#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace std;



			//caractéristiques rectangle blanc
//---------------------------------------------------------
struct Rectangle{
	int height = 0;
	int width = 3;
	int x_location = 0;
	int y_location = 0;
	sf::Color white = sf::Color(255, 255, 255);
};
//---------------------------------------------------------



			//crée plusieurs rectangles de hauteurs aléatoires aléatoires et les place dans un vecteur
//---------------------------------------------------------
void FillVector(Rectangle rectangle, vector<Rectangle> &pos, sf::Image i) {
	int x_position = 0; //on commence à placer les rectangles en bas à gauche de la fenêtre jusqu'en bas à droite
	while (x_position < i.getSize().x) {
		rectangle.height = rand() % i.getSize().y - 50; // "-50" pour ne pas avoir de rectangles touchant le haut de la fenêtre
		if (rectangle.height < 5) {
			rectangle.height = 5; //si la hauteur est inférieur à 5, alors on dit que le rectangle a une hauteur de 5
		}
		rectangle.x_location = x_position;
		rectangle.y_location = i.getSize().y - rectangle.height;
		pos.push_back(rectangle); //inscrit chaque rectangle dans le vecteur
		x_position += 3;
	}
}
//---------------------------------------------------------



			//affiche les rectangles à l'écran
//---------------------------------------------------------
void PrintVector(sf::Image &im, vector<Rectangle> rectangle) {
	for (int i = 0; i < rectangle.size(); i++) {
		for (int X = 0; X < rectangle[i].width; X++) {
			for (int Y = 0; Y < rectangle[i].height; Y++) {
				im.setPixel(rectangle[i].x_location + X, rectangle[i].y_location + Y, rectangle[i].white); //colore en blanc les endroits où doivent se placer les rectangles
			}
		}
	}
}
//---------------------------------------------------------



			//algorithme de tri classique + redessine les rectangles à l'écran au fur et à mesure du tri
//---------------------------------------------------------
void Sorting(std::vector<Rectangle> &rectangle, sf::Image &im, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite) {
	Rectangle temp;

	for (int i = 0; i < rectangle.size() - 1; i++) {
		if (rectangle[i].height > rectangle[i + 1].height) { //si le rectangle actuel est plus grand que le rectangle devant lui, alors interchanger leur place
			window.clear();

						//recolorie le plus grand rectangle à sa nouvelle place à l'écran
			//---------------------------------------------------------
			for (int X = 0; X < rectangle[i].width; X++) {
				for (int Y = 0; Y < rectangle[i].height; Y++) {
					im.setPixel(rectangle[i + 1].x_location + X, rectangle[i].y_location + Y, rectangle[i].white); 
			}}
			//---------------------------------------------------------

						//supprime visuellement le plus grand rectangle de sa dernière place
			//---------------------------------------------------------
			for (int X = 0; X < rectangle[i].width; X++) {
				for (int Y = 0; Y < rectangle[i].height; Y++) {
					im.setPixel(rectangle[i].x_location + X, rectangle[i].y_location + Y, sf::Color(0, 0, 0));
			}}
			//---------------------------------------------------------

						//recolorie le plus petit rectangle de sa dernière place à l'écran
			//---------------------------------------------------------
			for (int X = 0; X < rectangle[i+1].width; X++) {
				for (int Y = 0; Y < rectangle[i+1].height; Y++) {
					im.setPixel(rectangle[i].x_location + X, rectangle[i+1].y_location + Y, rectangle[i].white);
			}}
			//---------------------------------------------------------

						//remplace les positions numériques des rectangles dans leur vecteur
			//---------------------------------------------------------
			int xTemp = rectangle[i].x_location;
			rectangle[i].x_location = rectangle[i + 1].x_location;
			rectangle[i + 1].x_location = xTemp;
			temp = rectangle[i];
			rectangle[i] = rectangle[i + 1];
			rectangle[i + 1] = temp;
			//---------------------------------------------------------

			//refresh la fenêtre
			texture.loadFromImage(im);
			sprite.setTexture(texture);
			window.draw(sprite);
			window.display();
		}
	}
}
//---------------------------------------------------------


int main(){
	cout << "PRESS SPACE TO INSTIGATE THE APPLICATION.";
	srand(time(NULL));
	int width = 900;
	int height = 620;
	bool spaceIspressed = false;
	sf::RenderWindow window(sf::VideoMode(width, height), "Mere Sorting Visualizer | Project For My NSI Class");
	sf::Event ev;
	sf::Image image;
	image.create(width, height);

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			image.setPixel(i, j, sf::Color(0, 0, 0)); //rempli le background en noir
		}
	}

	sf::Sprite sprite;
	sf::Texture texture;
	Rectangle rectangle;
	vector<Rectangle> rectangleV;

	FillVector(rectangle, rectangleV, image);
	PrintVector(image, rectangleV);

	texture.loadFromImage(image);
	sprite.setTexture(texture);

	while (window.isOpen()){
		while (window.pollEvent(ev)){
			if (ev.type == sf::Event::Closed){
				window.close();
			}
			if (ev.type == sf::Event::KeyReleased){
				if (ev.key.code == sf::Keyboard::Space){
					spaceIspressed = true;
				}
			}
		}
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.clear();

		if (spaceIspressed){ //quand space est pressé alors enclencher le sorting
			Sorting(rectangleV, image, window, texture, sprite);
		}

		window.draw(sprite);
		window.display();
	}
	return 0;
}
