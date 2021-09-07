         /*  JUMP DINO JUMP * /
/********************************************/
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <SPI.h>
#include <EEPROM.h>
/********************************************/
#define ok  7
#define up  6
#define down  5
#define back  4

#define DC    9
#define RES   8
#define SDA   11
#define SCL   13

#define RAMA 0xe5e5
#define LAYAL 0xe0e0
#define RED1 0xc0c0
#define DINO 0x4646
#define rank1 0x6767
#define rank2 0x6666
#define rank3 0x6565

#define SCR_WD   240
#define SCR_HT   240
Arduino_ST7789 lcd = Arduino_ST7789(DC, RES);
/********************************************/
int posicao = 0;
int voltar = 0;
int rank [3];
/********************************************/
void capa_principal ();
void menu();
int escolhe_menu ();
void select_ok ();
void jogar();
void ranking();
void creditos();
void sobre ();
void ET ();
/********************************************/
void setup()
{
  lcd.init(SCR_WD, SCR_HT);
  pinMode (ok, INPUT_PULLUP);
  pinMode (up, INPUT_PULLUP);
  pinMode (down, INPUT_PULLUP);
  pinMode (back, INPUT_PULLUP);

  capa_principal ();
  EEPROM[20] = 0;
}
/********************************************/
void loop()
{
  menu();
  escolhe_menu();

}
/********************************************/
void capa_principal ()
{
  lcd.clearScreen ();
  lcd.fillScreen(0202);
  lcd.drawRect(0, 0, 240, 240, GREEN);
  lcd.setTextColor(RED);
  lcd.setTextSize(6.9);
  lcd.setCursor(59, 30);
  lcd.println("JUMP");
  lcd.setTextColor(GREEN);
  lcd.setCursor(60, 100);
  lcd.println("DINO");
  lcd.setTextColor(YELLOW);
  lcd.setCursor(59, 170);
  lcd.println("JUMP");
  delay(3000);

}
/********************************************/
void menu()
{
  lcd.clearScreen ();
  lcd.fillScreen(BLACK);
  lcd.setTextColor(RED);
  lcd.setTextSize(3.7);
  lcd.setCursor(36, 10);
  lcd.println("JUMP");
  delay(240);
  lcd.setTextColor(GREEN);
  lcd.setCursor(90, 45);
  lcd.println("DINO");
  delay(240);
  lcd.setTextColor(YELLOW);
  lcd.setCursor(145, 10);
  lcd.println("JUMP");
  delay(240);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2.3);
  lcd.setCursor (85, 90);
  lcd.println("Jogar");
  delay(220);
  lcd.setCursor(85, 120);
  lcd.println("Ranking");
  delay(220);
  lcd.setCursor(85, 150);
  lcd.println("Creditos");
  delay(220);
  lcd.setCursor(85, 180);
  lcd.println("Sobre");

}
/********************************************/
int escolhe_menu ()
{
  while (true)
  {
    ET ();
    if (digitalRead(down) == LOW)
    {
      posicao++; delay(500);
    }

    if (digitalRead(up) == LOW)
    {
      posicao--; delay(500);
    }

    if ( posicao > 3 )
    {
      posicao = 0;
    }

    if ( posicao < 0 )
    {
      posicao = 3;
    }

    if ( posicao == 0)
    {
      lcd.setTextColor (YELLOW);
      lcd.setCursor (65, 90);
      lcd.print (">");
    }

    else {
      lcd.fillRect (65, 90, 20, 20, BLACK);
    }

    if (posicao == 1)
    {
      lcd.setTextColor (YELLOW);
      lcd.setCursor (65, 120);
      lcd.print (">");
    }
    else {
      lcd.fillRect (65, 120, 20, 20, BLACK);
    }

    if (posicao == 2)
    {
      lcd.setTextColor (YELLOW);
      lcd.setCursor (65, 150);
      lcd.print (">");
    }
    else {
      lcd.fillRect (65, 150, 20, 20, BLACK);
    }

    if (posicao == 3)
    {
      lcd.setTextColor (YELLOW);
      lcd.setCursor (65, 180);
      lcd.print (">");
    }
    else {
      lcd.fillRect (65, 180, 20, 20, BLACK);
    }

    select_ok();

    if (voltar == 1)
    {
      voltar = 0;
      break;
    }
  }
}
/********************************************/
void select_ok ()
{
  if (digitalRead (ok) == LOW && posicao == 0)
  {
    lcd.fillScreen (BLACK);
    jogar();
    voltar = 1;
    return;
  }
  if (digitalRead (ok) == LOW && posicao == 1)
  {
    lcd.fillScreen (BLACK);
    ranking();
    voltar = 1;
    return;
  }
  if (digitalRead (ok) == LOW && posicao == 2)
  {
    lcd.fillScreen (BLACK);
    creditos();
    voltar = 1;
    return;
  }
  if (digitalRead (ok) == LOW && posicao == 3)
  {
    lcd.fillScreen (BLACK);
    sobre();
    voltar = 1;
    return;
  }
  if (digitalRead (back) == LOW)
  {
    lcd.clearScreen();
    menu();
    escolhe_menu();
    voltar = 1;
    return;
  }
}
/********************************************/
void jogar()
{
  int xmeteoro, ymeteoro;
  int x, y; // variavel auxiliar
  x = 260;
  y = 155;
  int xdino, ydino;
  int oldxdino, oldydino;
  xdino = 50;
  ydino = 155;

  int scorePlayer = 0;

  do
  {
    xmeteoro = x;
    ymeteoro = y;
    oldxdino = xdino;
    oldydino = ydino;

    // pulo
    if (digitalRead (up) == LOW && ydino > 75)
    {
      // ele vai subir 6 pixels
      ydino -= 6;
    }

    /*  tamanho do quadrado  */
    if (x <= xdino + 20 && y <= ydino && y <= ydino + 20) {

      // BATIDA
      delay(200);
      lcd.clearScreen ();

      lcd.drawRect(0, 0, 240, 240, RAMA);
      lcd.setTextSize (6);
      lcd.setTextColor (WHITE);
      lcd.setCursor (20, 30);
      lcd.print ("GAME");
      lcd.setCursor (75, 180);
      lcd.print ("OVER");

      lcd.fillRect(33, 130, 2.5, 10, DINO);//perna esquerda.
      lcd.fillRect(40, 130, 2.5, 10, DINO);//perna direita.
      lcd.fillRoundRect(30, 122, 20, 9, 20, DINO);//corpo
      lcd.fillCircle(48, 120, 5.3, DINO);//pescoço
      lcd.fillCircle(53, 112, 4.5, DINO);//cabeça
      lcd.fillCircle(70, 130, 6, RED1);//meteoro

      lcd.setTextSize(3);
      lcd.setCursor(100, 116);
      lcd.print(scorePlayer);
      delay(2000);

      int r =  EEPROM[20];
      int rank[3];
      rank[0] = EEPROM[21];
      rank[1] = EEPROM[22];
      rank[2] = EEPROM[23];


      if (r == 0 && rank[0] < scorePlayer)
      {
        EEPROM[21] = scorePlayer;
      }
      if (r == 1 && rank[1] < scorePlayer)
      {
        EEPROM[22] = scorePlayer;
      }
      if (r == 2 && rank[2] < scorePlayer)
      {
        EEPROM[23] = scorePlayer;
      }
      r++;

      EEPROM[20] = r;

      return;
    }

    // queda
    if (ydino < 155)
    {
      ydino += 2;//velocidade do dino
    }
    if (oldxdino != xdino || oldydino != ydino)
    {
      lcd.fillRect(oldxdino, oldydino, 20, 20, BLACK);
    }
    lcd.fillRect(xdino, ydino, 20, 20, GREEN);

    x -= 1.5;//velocidade do obstaculo
    if (xmeteoro != x  || ymeteoro != y)//meteoro
    {
      lcd.fillCircle(xmeteoro, ymeteoro, 6, BLACK);//apagando a posicao antiga
    }
    lcd.fillCircle(x, y, 6, RED1);
    delay(5);

    if (x < 0)
    {
      lcd.fillCircle(0, ymeteoro, 6, BLACK);
      x = 240;

      /* PONTUAÇÃO DO PLAYER */
      lcd.fillRect (0, 20, 240, 20, BLACK);
      lcd.setTextColor (WHITE);
      scorePlayer ++;
      lcd.setCursor (40, 20);
      lcd.print ("SCORE");
      lcd.setCursor (140, 20);
      lcd.print (scorePlayer);
    }

    if (digitalRead (back) == LOW)
    {
      return;
    }
  } while (true);
}

/********************************************/
void ranking()
{
  int x, j, i; // variaveis auxiliares

  lcd.setCursor(60, 20);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(3.7);
  lcd.print("RANKING");

  int rank[3];

  rank[0] = EEPROM[21];
  rank[1] = EEPROM[22];
  rank[2] = EEPROM[23];

  for (i = 0; i < 2; i++)
  {
    for (j = i + 1; j < 3; j++)
    {
      if (rank[i] < rank[j])
      {
        x = rank[i];
        rank[i] = rank[j];
        rank[j] = x;
      }
    }
  }


  lcd.fillRect(0, 80, 240, 128, rank1);
  lcd.fillRect(0, 128, 240, 176, rank2);
  lcd.fillRect(0, 176, 240, 224, rank3);
  lcd.fillRect(0, 224, 240, 240, BLACK);
  lcd.setCursor(40, 93);
  lcd.print ("-  ");
  lcd.print (rank[0]);
  lcd.setCursor (40, 142);
  lcd.print ("-  ");
  lcd.print (rank[1]);
  lcd.setCursor (40, 189);
  lcd.print ("-  ");
  lcd.print (rank[2]);

  do
  {
    if (digitalRead (back) == LOW)
    {
      return;
    }
  } while (true);
}
/********************************************/
void creditos()
{
  lcd.fillRect(0, 90, 240, 145, RAMA);
  lcd.fillRect(0, 145, 240, 200, LAYAL);
  lcd.fillRect(0, 200, 240, 240, BLACK);

  lcd.setCursor(50, 20);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(3.7);
  lcd.print("CREDITOS");
  lcd.setCursor(60, 110);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2.5);
  lcd.print("RAMA NAIM");
  lcd.setCursor(40, 165);
  lcd.print("LAYAL AL WANNI");
  do
  {
    if (digitalRead (back) == LOW)
    {
      return;
    }
  } while (true);
}
/********************************************/
void sobre()
{
  lcd.setCursor(70, 20);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(3.7);
  lcd.print("SOBRE");
  lcd.setCursor(25, 70);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.print ("DINO ESTA FUGINDO");
  lcd.setCursor (20, 100);
  lcd.print ("DE ALIENIGENAS, E");
  lcd.setCursor (20, 130);
  lcd.print ("ESTA A CAMINHO DA");
  lcd.setCursor (20, 160);
  lcd.print ("TERRA.");
  lcd.setCursor (38, 210);
  lcd.fillRect(0, 193, 240, 240, RED);
  lcd.setTextSize(3.7);
  lcd.print ("AJUDE ELE");
  do
  {
    if (digitalRead (back) == LOW)
    {
      return;
    }
  } while (true);
}
/********************************************/
void ET ()
{
  int rand_x = random (240);
  int rand_y = random (240);
  lcd.drawPixel (rand_x, rand_y, GREEN);
  delay(150);
}
/********************************************/
