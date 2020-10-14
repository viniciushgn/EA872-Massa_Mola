#include <memory> //smart pointers
#include <iostream> //imput output
#include <SDL2/SDL.h>//SDL2
#include <SDL2/SDL_image.h>//SDL@



//MODEL_________________________________________________________________________

class ParametrosFisicos{
private:
  float posicao, velocidade, deltaT, c, k, massa, nIteracoes;
public:
  float getPosicao();
  float getVelocidade();
  float getDeltaT();
  float getC();
  float getK();
  float getMassa();
  int getNIteracoes();

  void setParametrosFisicos(float pos, float vel, float delT, float c_, float k_, float massa_, int n);
  void setPosicao(float pos);
  void setVelocidade(float vel);
  ParametrosFisicos();
};

float ParametrosFisicos::getPosicao(){
  return posicao;
}

float ParametrosFisicos::getVelocidade(){
  return velocidade;
}

float ParametrosFisicos::getDeltaT(){
  return deltaT;
}

float ParametrosFisicos::getC(){
  return c;
}

float ParametrosFisicos::getK(){
  return k;
}

float ParametrosFisicos::getMassa(){
  return massa;
}

void ParametrosFisicos::setParametrosFisicos(float pos, float vel, float delT, float c_,
   float k_, float massa_, int n){
  posicao = pos; velocidade = vel; deltaT = delT; c = c_; k = k_; massa = massa_;
  nIteracoes = n;
}

void ParametrosFisicos::setPosicao(float pos){
  posicao = pos;
}

void ParametrosFisicos::setVelocidade(float vel){
  velocidade = vel;
}

ParametrosFisicos::ParametrosFisicos(){
  posicao = 0; velocidade = 0; c = 0; k = 0; massa = 0;deltaT = 0;nIteracoes = 0;
}









//VIEW__________________________________________________________________________

class View{
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture *texture;
  SDL_Texture *texture2;
  SDL_Rect target;

public:
  View();
  void render(int x, int y);
};

View::View(){

//INICIALIZANDO VIDEO-----------------------------------------------------------
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


  if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
    std::cout << SDL_GetError();
  }
//CRIANDO JANELA----------------------------------------------------------------
window = nullptr;
window = SDL_CreateWindow("SDL2: massa mola",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN);
if (window==nullptr) { // Em caso de erro...
  std::cout << SDL_GetError();
  SDL_Quit();
}
//INICIALIANDO RENDERIZADOR-----------------------------------------------------
renderer = SDL_CreateRenderer(
    window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (renderer==nullptr) { // Em caso de erro...
  SDL_DestroyWindow(window);
  std::cout << SDL_GetError();
  SDL_Quit();
}
//CARREGANDO TEXTURAS-----------------------------------------------------------
// personagem
texture = IMG_LoadTexture(renderer, "./bola.jpg");
// fundo
texture2 = IMG_LoadTexture(renderer, "./park.jpeg");
// Quadrado onde a textura sera desenhada
target.x = 0;
target.y = 0;
SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);
//deletar
SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, texture2, nullptr, nullptr);
SDL_RenderCopy(renderer, texture, nullptr, &target);
SDL_RenderPresent(renderer);
  SDL_Delay(10);
//deletar-
}

void View::render(int x, int y){
target.x = x;
target.y = y;
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture2, nullptr, nullptr);
  SDL_RenderCopy(renderer, texture, nullptr, &target);
  SDL_RenderPresent(renderer);
  // Delay para diminuir o framerate
  SDL_Delay(10);
}









//CONTROLLER____________________________________________________________________

class Controller{
private:
   ParametrosFisicos& model;
   View& view;

public:
  Controller(ParametrosFisicos& model, View& view);
  void update() ;
};

Controller::Controller(ParametrosFisicos& model_, View& view_) : model(model_), view(view_){

//como deixo o mesmo nome (parametro e variavel privada) e mesmo assim passo o valor?
//devo usar o indicador const para o model e o view privado? !!!!!!!!!!!!!!!
}

void Controller::update(){

model.setVelocidade(model.getVelocidade() + model.getDeltaT()  *(((  -model.getC()*model.getVelocidade()  ) -model.getK() *model.getPosicao())/model.getMassa()));
model.setPosicao(model.getPosicao() + model.getVelocidade() * model.getDeltaT());
  //Vnova = vi + ti*(((-ci*Vnova) -ki*Pnova)/mi);
  //Pnova = Pnova + Vnova * ti;}

view.render(150,(int)model.getPosicao());

}




int main(){
float pi,vi,ti,ci,ki,mi;
int ni;
float Pnova, Vnova;


std::cout << "Entre com Posicao, Velocidade, deltaT, c, k, massa e N:" << std::endl;
std::cin >> pi;
std::cin >> vi;
std::cin >> ti;
std::cin >> ci;
std::cin >> ki;
std::cin >> mi;
std::cin >> ni;



ParametrosFisicos p1;
p1.setParametrosFisicos(pi,vi,ti,ci,ki,mi,ni);

View tela;

Controller c1 (p1,tela);

for(int i = 0; i<1000; i++){
c1.update();
}


return 0;
}
