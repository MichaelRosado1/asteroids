#include "Bullet.h"
#include <iostream>


Bullet::Bullet(int id) : bullet_id(id) {
	std::cout << "Bullet created\n";
}

Bullet::~Bullet() {
	std::cout << "Bullet destruction\n";
}

int Bullet::getId() {
	return bullet_id;
}