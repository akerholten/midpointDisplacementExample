#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
std::random_device rnd;
std::mt19937 rng(rnd());
std::uniform_real_distribution<float> random(-150, 150.0f);
const int WINDOWWIDTH = 800;
const int WINDOWHEIGHT = 800;
const int POINTS =257;
float data[POINTS];
float lineLength(int points) {
return WINDOWWIDTH / (points - 1.0);
}
void calculate() {
float alpha = 1.0f;
rng.seed(1000.0f);
data[0] = random(rng) * alpha;
data[POINTS - 1] = random(rng) * alpha;
for (int i = POINTS - 1; i > 1; i /= 2)
{
for (int j = i / 2; j < POINTS - 1; j += i) {
data[j] = ((data[j - i / 2] + data[j + i / 2]) / 2) + (random(rng) * alpha);
std::cout << j << " " << j - i / 2 << " " << j + i / 2 << " " << i << std::endl;
}
alpha /= 2.0f;
}
}
int main() {
sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Midpoint displacement");
float length = lineLength(POINTS);

calculate();
bool stop = false;
while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
if (event.type == sf::Event::Closed)
window.close();
}
window.clear();
for (int i = 0; i < POINTS - 1; i += 1) {
//std::cout << data[i] << ’\n’;
sf::Vertex line[] =
{
sf::Vertex(sf::Vector2f((i * length), data[i] + (WINDOWHEIGHT / 2))),
sf::Vertex(sf::Vector2f((i + 1) * length, data[i + 1] + (WINDOWHEIGHT / 2)))
};
window.draw(line, 2, sf::Lines);
if (!stop)
std::cout << length << " " << i << std::endl;
sf::CircleShape s;
s.setRadius(10);
s.setOrigin(10, 10);
s.setFillColor(sf::Color::Yellow);
s.setPosition(800, 250);
window.draw(s);
}
stop = true;
window.display();
}
return 0;
}