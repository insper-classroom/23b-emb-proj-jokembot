import pyautogui
import serial
import argparse
import time
import logging
import pygame


pygame.init()

class MyControllerMap:
    def __init__(self):
        self.button = {
            'SPACE': 'SPACE',
            'I': '1',
            '2': '2',
            '3': '3',
            '4': '4',
            '5': '5',
            '6': '6',
            '7': '7',
            '8': '8',
            '9': '9', 
            'R': 'R', 
            'P': 'P', 
            'S': 'S'
        }



class SerialControllerInterface:
    def __init__(self, port, baudrate, game):
        self.ser = serial.Serial(port, baudrate=baudrate)
        self.mapping = MyControllerMap()
        self.incoming = '0'
        pyautogui.PAUSE = 0
        self.game = game
        self.handshake = False
        self.jogadas = 0
        self.rps = 'b'
        

    def update(self):

        while self.incoming != b'H' and self.handshake == False:
            self.ser.write('H'.encode('ascii'))
            logging.debug("Enviando handshake")
            self.incoming = self.ser.read()
            logging.debug("Received INCOMING hs: {}".format(self.incoming))
            
            if self.incoming == b'H':
                logging.debug("handshake!!!")
                self.handshake = True
               
        
        if self.incoming == b'H':
                logging.debug("handshake!!!")
                self.game.toggle_game_state(jogadas = 0, rps = self.rps)
                self.handshake = True 
                

        while self.incoming != b'X' and self.handshake == True:
            self.incoming = self.ser.read()
            logging.debug("Received INCOMING: {}".format(self.incoming))

        data = self.ser.read()
        logging.debug("Received DATA: {}".format(data))

        if data == b'1':
            logging.info("KEYDOWN SPACE")
            self.game.toggle_game_state(jogadas = 0, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['SPACE'])
        elif data == b'0':
            logging.info("KEYUP SPACE")
            pyautogui.keyUp(self.mapping.button['SPACE'])
        elif data == b'I':
            logging.info("KEYDOWN I")
            self.jogadas = 1
            self.game.toggle_game_state(jogadas = 1, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['1'])
        elif data == b'2':
            logging.info("KEYDOWN 2")
            self.jogadas = 2
            self.game.toggle_game_state(jogadas = 2, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['2'])
        elif data == b'3':
            logging.info("KEYDOWN 3")
            self.jogadas = 3
            self.game.toggle_game_state(jogadas = 3, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['3'])
        elif data == b'4':
            logging.info("KEYDOWN 4")
            self.jogadas = 4
            self.game.toggle_game_state(jogadas = 4, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['4'])
        elif data == b'5':
            logging.info("KEYDOWN 5")
            self.jogadas = 5
            self.game.toggle_game_state(jogadas = 5, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['5'])
        elif data == b'6':
            logging.info("KEYDOWN 6")
            self.jogadas = 6
            self.game.toggle_game_state(jogadas = 6, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['6'])
        elif data == b'7':
            logging.info("KEYDOWN 7")
            self.jogadas = 7
            self.game.toggle_game_state(jogadas = 7, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['7'])
        elif data == b'8':
            logging.info("KEYDOWN 8")
            self.jogadas = 8
            self.game.toggle_game_state(jogadas = 8, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['8'])
        elif data == b'9':
            logging.info("KEYDOWN 9")
            self.jogadas = 9
            self.game.toggle_game_state(jogadas = 9, rps = self.rps)
            pyautogui.keyDown(self.mapping.button['9'])
        elif data == b'R':
            logging.info("KEYDOWN R")
            self.game.toggle_game_state(jogadas = self.jogadas, rps = 'R')
            pyautogui.keyDown(self.mapping.button['R'])
        elif data == b'P':
            logging.info("KEYDOWN R")
            self.game.toggle_game_state(jogadas = self.jogadas, rps = 'P')
            pyautogui.keyDown(self.mapping.button['S'])
        elif data == b'S':
            logging.info("KEYDOWN R")
            self.game.toggle_game_state(jogadas = self.jogadas, rps = 'S')
            pyautogui.keyDown(self.mapping.button['S'])
       


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
        pyautogui.keyDown(self.mapping.button['1'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['1'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['2'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['2'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['3'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['3'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['4'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['4'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['5'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['5'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['6'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['6'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['7'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['7'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['8'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['8'])
        logging.info("[Dummy] Pressed A button")
        time.sleep(1)
        pyautogui.keyDown(self.mapping.button['9'])
        time.sleep(0.1)
        pyautogui.keyUp(self.mapping.button['9'])
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
        self.font = pygame.font.Font('font/PressStart2P-Regular.ttf', 20)
        self.font2 = pygame.font.Font('font/PressStart2P-Regular.ttf', 100)
        self.texto_inicial = self.font.render('Aperte o botão para jogar', True, self.black)
        self.pedra_text = self.font.render('Pedra', True, self.black)
        self.papel_text = self.font.render('Papel', True, self.black)
        self.tesoura_text = self.font.render('Tesoura', True, self.black)
        self.win_text = self.font.render('Você venceu', True, self.green)
        self.tie_text = self.font.render('É um empate', True, self.yellow)
        self.lose_text = self.font.render('Você perdeu', True, self.red)
        self.computer_text = self.font.render('', True, self.black)

        self.vitorias = 0
        self.derrotas = 0
        self.empates = 0

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

    def teladejogadas(self):
        self.window.fill((0, 0, 0))
        self.text_jogadas = self.font.render("Quantas vezes você quer jogar?", True, self.white)
        self.window.blit(self.text_jogadas, (250, 400))
        pygame.display.flip()

    def teladeregras(self, jogadas):
        self.window.fill((0, 0, 0))
        self.text_regras = self.font.render("O jogo funciona da seguinte forma:", True, self.white)
        self.window.blit(self.text_regras, (180, 200))
        pygame.display.flip()
        time.sleep(2)
        self.text_regras2 = self.font.render("Todo começo de rodada voce terá 3", True, self.white)
        self.window.blit(self.text_regras2, (180, 250))
        self.text_regras3 = self.font.render("segundos para escolher sua jogada:", True, self.white)
        self.window.blit(self.text_regras3, (180, 300))
        pygame.display.flip()
        time.sleep(2)
        self.text_regras4 = self.font.render("Pedra, Papel ou Tesoura!", True, self.white)
        self.window.blit(self.text_regras4, (300, 350))
        pygame.display.flip()
        time.sleep(2)
        self.window.fill((0, 0, 0))
        self.text_regras5 = self.font.render("Está pronto(a)?", True, self.white)
        self.window.blit(self.text_regras5, (320, 200))
        pygame.display.flip()
        time.sleep(1)
        self.text_regras6 = self.font.render("Vamos começar em alguns segundos!", True, self.white)
        self.window.blit(self.text_regras6, (180, 250))
        pygame.display.flip()
        time.sleep(2)
        self.toggle_game_state(jogadas = jogadas, rps = 'b')

    def telaprejogo(self, jogadas):

        self.window.fill((0, 0, 0))
        self.text_tempo = self.font2.render(f"Jogada {jogadas-jogadas+1}", True, self.white)
        self.window.blit(self.text_tempo, (100, 200))
        pygame.display.flip()
        time.sleep(1)

        self.window.fill((0, 0, 0))
        self.text_tempo = self.font2.render("3", True, self.white)
        self.window.blit(self.text_tempo, (450, 350))
        pygame.display.flip()
        time.sleep(1)

        self.window.fill((0, 0, 0))
        self.text_tempo = self.font2.render("2", True, self.white)
        self.window.blit(self.text_tempo, (450, 350))
        pygame.display.flip()
        time.sleep(1)

        self.window.fill((0, 0, 0))
        self.text_tempo = self.font2.render("1", True, self.white)
        self.window.blit(self.text_tempo, (450, 350))
        pygame.display.flip()
        time.sleep(1)

        self.window.fill((0, 0, 0))
        pygame.display.flip()
        
        
    def telajogo(self, jogadas, rps):
        if rps =='R':
            self.window.fill((0, 0, 0))
            self.text_tempo = self.font2.render("PAPEL", True, self.white)
            self.window.blit(self.text_tempo, (450, 350))
            pygame.display.flip()
            time.sleep(1)
        
        if rps =='P':
            self.window.fill((0, 0, 0))
            self.text_tempo = self.font2.render("TESOURA", True, self.white)
            self.window.blit(self.text_tempo, (450, 350))
            pygame.display.flip()
            time.sleep(1)
        
        if rps =='S':
            self.window.fill((0, 0, 0))
            self.text_tempo = self.font2.render("PEDRA", True, self.white)
            self.window.blit(self.text_tempo, (450, 350))
            pygame.display.flip()
            time.sleep(1)
        
        else:
            self.window.fill((0, 0, 0))
            self.text_tempo = self.font.render("NÂO RECEBEMOS INFORMAÇÔES :(", True, self.white)
            self.window.blit(self.text_tempo, (300, 350))
            pygame.display.flip()
            time.sleep(1)

        self.toggle_game_state(self, jogadas - 1, rps)


    def tela_checagem(self, jogadas, rps):
        self.window.fill((0, 0, 0))
        self.text_tempo = self.font.render("Qual foi sua jogada?", True, self.white)
        self.window.blit(self.text_tempo, (200, 200))
        pygame.display.flip()
        time.sleep(1)
        self.text_tempo = self.font.render("1- Pedra", True, self.white)
        self.window.blit(self.text_tempo, (400, 250))
        self.text_tempo = self.font.render("2- Papel", True, self.white)
        self.window.blit(self.text_tempo, (400, 300))
        self.text_tempo = self.font.render("3- Tesoura", True, self.white)
        self.window.blit(self.text_tempo, (400, 350))
        pygame.display.flip()
        time.sleep(1)



    def toggle_game_state(self, jogadas, rps):
        if self.game_state == 0:
            pygame.init()
            self.telaconfiguracaoinicial()
            print("Mostrando tela inicial!")
            self.game_state = 1

        elif self.game_state == 1:
            self.game_state = 2
            self.teladeregras(jogadas = jogadas)
            print("Mostrando tela de regras!")

        elif self.game_state == 2:
            self.game_state = 3
            self.teladejogadas()
            print("Mostrando tela de jogadas!")
            
        elif self.game_state == 3:
            if jogadas > 0:
                print("entrei aquiiii")
                self.game_state = 4
            else: 
                self.game_state = 6
            self.telaprejogo(jogadas = jogadas)
            print(f"Mostrando tela pré jogo!, jogadas = {jogadas}")
            

        elif self.game_state == 4:
            self.telajogo(jogadas = jogadas, rps = rps)
            print("Mostrando tela do jogo!")
            if jogadas > 0:
                self.game_state = 5
            else:
                self.game_state = 6
        
        elif self.game_state == 5:
            self.tela_checagem(self, jogadas, rps)

            
            



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
