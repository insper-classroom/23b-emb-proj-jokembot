import pyautogui
import serial
import argparse
import time
import logging
import pygame

pygame.init()

class MyControllerMap:
    def __init__(self):
        self.button = {'SPACE': 'SPACE'}

class SerialControllerInterface:
    def __init__(self, port, baudrate, game):
        self.ser = serial.Serial(port, baudrate=baudrate)
        self.mapping = MyControllerMap()
        self.incoming = '0'
        pyautogui.PAUSE = 0
        self.game = game

    def update(self):
        while self.incoming != b'X':
            self.incoming = self.ser.read()
            logging.debug("Received INCOMING: {}".format(self.incoming))

        data = self.ser.read()
        logging.debug("Received DATA: {}".format(data))

        self.ser.write('hello'.encode('ascii'))

        if data == b'1':
            logging.info("KEYDOWN SPACE")
            self.game.toggle_game_state()
            pyautogui.keyDown(self.mapping.button['SPACE'])
        elif data == b'0':
            logging.info("KEYUP SPACE")
            pyautogui.keyUp(self.mapping.button['SPACE'])

        self.incoming = self.ser.read()

class DummyControllerInterface:
    def __init__(self):
        self.mapping = MyControllerMap()

    def update(self):
        pyautogui.keyDown(self.mapping.button['SPACE'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['SPACE'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)

def check_for_exit():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            return True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                return True
    return False

class Jokembot:
    def __init__(self):

        self.game_state = 0
        self.largura = 1000
        self.altura = 800

        self.grey = (128, 128, 128)
        self.yellow = (253,255,0)
        self.red = (200,0,0)
        self.black = (0,0,0)
        self.green = (0, 255, 0)
        self.white = (255, 255, 255)

        self.pedra_button = pygame.Rect(self.largura/4-75, self.altura/2, 150, 50)
        self.papel_button = pygame.Rect(self.largura/2-75, self.altura/2, 150, 50)
        self.tesoura_button = pygame.Rect(self.largura-self.largura/4-75, self.altura/2, 150, 50)
        self.font = pygame.font.Font('freesansbold.ttf', 32)
        self.texto_inicial = self.font.render('Aperte o botão para jogar', True, self.black)
        self.pedra_text = self.font.render('Pedra', True, self.black)
        self.papel_text = self.font.render('Papel', True, self.black)
        self.tesoura_text = self.font.render('Tesoura', True, self.black)
        self.win_text = self.font.render('Você venceu', True, self.green)
        self.tie_text = self.font.render('É um empate', True, self.yellow)
        self.lose_text = self.font.render('Você perdeu', True, self.red)
        self.computer_text = self.font.render('', True, self.black)

        self.window = pygame.display.set_mode((self.largura, self.altura))
        pygame.display.set_caption('Jokembot')

    def telaconfiguracaoinicial(self):
        self.fundo_inicial = pygame.transform.scale(pygame.image.load('imagens/jokembot.png').convert_alpha(), (self.largura, self.altura))
        self.window.fill((0, 0, 0))
        self.window.blit(self.fundo_inicial, (0, 0))
        self.texto_rect = self.texto_inicial.get_rect(topleft=(250, 400))
        self.texto_rect.inflate_ip(10*2, 10*2)
        pygame.draw.rect(self.window, self.white, self.texto_rect)
        self.window.blit(self.texto_inicial, (250, 400))
        pygame.display.flip()

    def teladejogo(self):
        

        self.window.fill((0, 0, 0))
        pygame.draw.rect(self.window, self.grey , self.pedra_button)
        pygame.draw.rect(self.window, self.yellow, self.papel_button)
        pygame.draw.rect(self.window, self.red, self.tesoura_button)

        self.window.blit(self.pedra_text, (self.pedra_button.centerx-40, self.pedra_button.centery-15))
        self.window.blit(self.papel_text, (self.papel_button.centerx-40, self.papel_button.centery-15))
        self.window.blit(self.tesoura_text, (self.tesoura_button.centerx-55, self.tesoura_button.centery-15))

        pygame.display.flip()
        

    def toggle_game_state(self):
        if self.game_state == 0:
            pygame.init()
            self.telaconfiguracaoinicial()
            print("Mostrando tela inicial!")
            self.game_state = 1
        elif self.game_state == 1:
            self.teladejogo()
            print("Mostrando tela de jogo!")
            
            



if __name__ == '__main__':
    jogo = Jokembot()
    interfaces = ['dummy', 'serial']
    argparse = argparse.ArgumentParser()
    argparse.add_argument('serial_port', type=str)
    argparse.add_argument('-b', '--baudrate', type=int, default=9600)
    argparse.add_argument('-c', '--controller_interface', type=str, default='serial', choices=interfaces)
    argparse.add_argument('-d', '--debug', default=False, action='store_true')
    args = argparse.parse_args()
    if args.debug:
        logging.basicConfig(level=logging.DEBUG)

    print("Connection to {} using {} interface ({})".format(args.serial_port, args.controller_interface, args.baudrate))
    if args.controller_interface == 'dummy':
        controller = DummyControllerInterface()
    else:
        controller = SerialControllerInterface(port=args.serial_port, baudrate=args.baudrate, game=jogo)

    while True:
        if check_for_exit():
            break
        controller.update()

    pygame.quit()  
