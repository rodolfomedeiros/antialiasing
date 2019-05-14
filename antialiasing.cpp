#include "antialiasing.h"

using namespace std;

void antiAliasing(
    int width,
    int height,
    int a,
    int l,
    unsigned char * R,
    unsigned char * G,
    unsigned char * B,
    PIXEL * *result,
    char * passaBaixa
){

  //tamanho total do vetor matriz da imagem original
  int size = width * height;

  //tamanho dos filtros de aguçamento e suavizacao
  unsigned char tamMatriz = 9;

  //passa alta horizontal (default)
  char passaAlta[] = {-1, -1, -1, 2, 2, 2, -1, -1, -1};

  //somatorio da matriz passa baixa
  unsigned char somatorioMatriz = somarMatriz(passaBaixa, tamMatriz);

  //variaveis temporarias
  double x, y;
  int pos, modulo;
  int dataModulo;
  int dataPosition[tamMatriz];
  int guardarPosicao[tamMatriz];
  unsigned char guardarY[tamMatriz];
  PIXEL * rgb;

  // percorrendo a matriz da imagem original
  for (int i = 0; i < size; i++){
    dataModulo = 0;
    // processo de rotacao
    for (int angulo = 0, radiano; angulo < 180; angulo += a){
      modulo = 0;
      radiano = angulo * PI / 180.0;

      //-1,1
      x = -cos(radiano) - sin(radiano);
      y = -sin(radiano) + cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[0] = pos;
      guardarY[0] = obterIntensidade(R, G, B, pos);
      //0,1
      x = -sin(radiano);
      y = cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[1] = pos;
      guardarY[1] = obterIntensidade(R, G, B, pos);
      //1,1
      x = cos(radiano) - sin(radiano);
      y = sin(radiano) + cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[2] = pos;
      guardarY[2] = obterIntensidade(R, G, B, pos);
      //-1,0
      x = -cos(radiano);
      y = -sin(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[3] = pos;
      guardarY[3] = obterIntensidade(R, G, B, pos);
      //0,0
      guardarPosicao[4] = i;
      guardarY[4] = obterIntensidade(R, G, B, i);
      //1,0
      x = cos(radiano);
      y = sin(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[5] = pos;
      guardarY[5] = obterIntensidade(R, G, B, pos);
      //-1,-1
      x = -cos(radiano) + sin(radiano);
      y = -sin(radiano) - cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[6] = pos;
      guardarY[6] = obterIntensidade(R, G, B, pos);
      //0,-1
      x = sin(radiano);
      y = -cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[7] = pos;
      guardarY[7] = obterIntensidade(R, G, B, pos);
      //1,-1
      x = cos(radiano) + sin(radiano);
      y = sin(radiano) - cos(radiano);
      pos = buscarPosicao(i, width, height, round(x), round(y));
      guardarPosicao[8] = pos;
      guardarY[8] = obterIntensidade(R, G, B, pos);

      //obtendo o modulo de deteccao a partir do angulo respectivo.
      for (int k = 0; k < tamMatriz; k++){
        modulo += (guardarY[k] * passaAlta[k]);
      }

      //verificando o melhor modulo de deteccao e guardando as informacoes da melhor rotacao com base no modulo obtido.
      if (abs(modulo) > dataModulo){
        dataModulo = abs(modulo);
        for (int k = 0; k < tamMatriz; k++){
          dataPosition[k] = guardarPosicao[k];
        }
      }
    }

    //informacoes do pixel original (para os pixels que não estao em borda)
    rgb = new PIXEL;
    rgb->r = R[i];
    rgb->g = G[i];
    rgb->b = B[i];
    rgb->l = 0;
    rgb->x = i % width;
    rgb->y = i / width;

    //operacao de suavizacao, se 'modulo' atender o criterio do limiar minimo de deteccao.
    if (dataModulo >= l){
      rgb->r = 0;
      rgb->g = 0;
      rgb->b = 0;
    
      for (int k = 0; k < tamMatriz; k++){
        pos = dataPosition[k];
        // se a posicao for nula, pula a operacao.
        if(pos != size){
          rgb->r += round((R[pos] * passaBaixa[k]/somatorioMatriz));
          rgb->g += round((G[pos] * passaBaixa[k]/somatorioMatriz));
          rgb->b += round((B[pos] * passaBaixa[k]/somatorioMatriz));
        }
      }
      rgb->l = 255;
    }

    // salvando o pixel no vetor resultado
    result[i] = rgb;
  }
}

// descobre a posição do pixel no vetor (bidimensional para unidimensional)
int buscarPosicao(int i, int width, int height, int x, int y){
  int v;
  

  // detectando a posicao no vetor
  if (x == -1 && y == 1){
    v = i + width - 1;
  }
  if (x == 0 && y == 1){
    v = i + width;
  }
  if (x == 1 && y == 1){
   v = i + width + 1;
  }
  if (x == -1 && y == 0){
    v = i - 1;
  }
  if (x == 0 && y == 0){
    return i;
  }
  if (x == 1 && y == 0){
    v = i + 1;
  }
  if (x == -1 && y == -1){
    v = i - width - 1;
  }
  if (x == 0 && y == -1){
    v = i - width;
  }
  if (x == 1 && y == -1){
    v = i - width + 1;
  }

  int xP = v % width;
  int yP = v / width;

  //verificacao dos limites da imagem
  if(xP < 0 || xP >= width || yP < 0 || yP >= height){
    // retorno com valor direcionado para uma posicao nula (0).
    return height*width;
  }else return v;
}

// obter a luminancia (Y) do pixel qualquer
int obterIntensidade(
    unsigned char *dataRed,
    unsigned char *dataGreen,
    unsigned char *dataBlue,
    int pos){
  return round(0.299 * dataRed[pos] + 0.587 * dataGreen[pos] + 0.114 * dataBlue[pos]);
}

// obter o somatorio dos valores dos filtros passa baixa
unsigned char somarMatriz(char * matriz, unsigned char tam){
  unsigned char valor = 0;
  for(int i = 0; i < tam; i++){
    valor += matriz[i];
  }

  return valor;
}

// gerando as imagens resultantes com OpenCV
void save(int x, int y, int t, PIXEL * r[]){
  
  cv::Mat img_saida(y, x, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat img_inversa(y, x, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat img_R(y, x, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat img_G(y, x, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat img_B(y, x, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat img_luminance(y, x, CV_8UC3, cv::Scalar(0,0,0));

  PIXEL * p;
  for(int i = x + 1; i < t - x - 1; i++){
    p = r[i];
    img_saida.at<cv::Vec3b>(y - p->y, p->x)[0] = p->b;
    img_saida.at<cv::Vec3b>(y - p->y, p->x)[1] = p->g;
    img_saida.at<cv::Vec3b>(y - p->y, p->x)[2] = p->r;
    img_R.at<cv::Vec3b>(y - p->y, p->x)[2] = p->r;
    img_G.at<cv::Vec3b>(y - p->y, p->x)[1] = p->g;
    img_B.at<cv::Vec3b>(y - p->y, p->x)[0] = p->b;
    if(p->l != 0){
      img_luminance.at<cv::Vec3b>(y - p->y, p->x)[0] = p->l;
      img_luminance.at<cv::Vec3b>(y - p->y, p->x)[1] = p->l;
      img_luminance.at<cv::Vec3b>(y - p->y, p->x)[2] = p->l;
    }
  }

  //salvar invertendo as cores
  cv::bitwise_not(img_saida, img_inversa);

  cv::imwrite("img_saida.png", img_saida);
  cv::imwrite("img_cor_invertida.png", img_inversa);
  cv::imwrite("img_cor_R.png", img_R);
  cv::imwrite("img_cor_G.png", img_G);
  cv::imwrite("img_cor_B.png", img_B);
  cv::imwrite("img_bordas.png", img_luminance);

  fourier();

}

// espectro de fourier
void fourier(){

  cv::Mat I = cv::imread("img_saida.png", cv::IMREAD_GRAYSCALE);
  if( I.empty()) return;

  cv::Mat padded;                            //expand input image to optimal size
  int m = cv::getOptimalDFTSize( I.rows );
  int n = cv::getOptimalDFTSize( I.cols ); // on the border add zero values
  cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

  cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
  cv::Mat complexI;
  cv::merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

  cv::dft(complexI, complexI);            // this way the result may fit in the source matrix

  // compute the magnitude and switch to logarithmic scale
  // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
  cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
  cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
  cv::Mat magI = planes[0];

  magI += cv::Scalar::all(1);                    // switch to logarithmic scale
  cv::log(magI, magI);

  // crop the spectrum, if it has an odd number of rows or columns
  magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

  // rearrange the quadrants of Fourier image  so that the origin is at the image center
  int cx = magI.cols/2;
  int cy = magI.rows/2;

  cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
  cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // Top-Right
  cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // Bottom-Left
  cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

  cv::Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);

  q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
  q2.copyTo(q1);
  tmp.copyTo(q2);

  cv::normalize(magI, magI, 0, 255, cv::NORM_MINMAX); // Transform the matrix with float values into a
                                          // viewable image form (float between values 0 and 1).

  cv::imwrite("img_escala_de_cinza.png", I);
  cv::imwrite("img_espectro_de_fourier.png", magI);

  //cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);
  
  //cv::imshow("Input Image"       , I   );    // Show the result
  //cv::imshow("spectrum magnitude", magI);
  cv::waitKey();

}