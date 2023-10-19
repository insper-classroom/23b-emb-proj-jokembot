import pyautogui
import serial
import argparse
import time
import logging
import pygame

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
        self.window = pygame.display.set_mode((self.largura, self.altura))
        pygame.display.set_caption('Jokembot')

    def telaconfiguracaoinicial(self):
        self.fundo_inicial = pygame.transform.scale(pygame.image.load('imagens/jokembot.png').convert_alpha(), (self.largura, self.altura))
        self.window.fill((0, 0, 0))
        self.window.blit(self.fundo_inicial, (0, 0))
        pygame.display.flip()

    def teladejogo(self):
        self.window.fill((0, 0, 0))
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
            self.game_state = 0


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
