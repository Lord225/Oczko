#pragma once
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <memory>

//Klasa karty
namespace Cards {
	enum Color {
		Club,
		Diamond,
		Heart,
		Spade
	};

	enum Value {
		card_Ace,
		card_2,
		card_3,
		card_4,
		card_5,
		card_6,
		card_7,
		card_8,
		card_9,
		card_10,
		card_Jack,
		card_Queen,
		card_King,
	};

	struct CardHash
	{
		Color color;
		Value value;
		CardHash(Color color, Value value){ 
			this->color = color;
			this->value = value;
		}
		CardHash(int color, int value): CardHash((Color)color, (Value)value) {
			assert(color >= 0 && color < 4);
			assert(value >= 0 && value < 13);
			
		}
		CardHash(const CardHash& cpy): CardHash(cpy.color, cpy.value){
			
		}

		static CardHash get_random_card() {
			return CardHash(rand() % 4, rand() % 13);
		}

		//Zwraca unikaln¹ wartoœæ dla ka¿dej karty
		size_t get_hash() {
			return (size_t)color + (size_t)value*4;
		}

		bool operator==(const CardHash& rsh) {
			return this->value == rsh.value && this->color == rsh.color;
		}

		//Zwraca unikaln¹ wartoœæ dla ka¿dej karty
		static size_t get_hash(size_t color, size_t value) {
			return (size_t)color + (size_t)value * 4;
		}
	};

}

