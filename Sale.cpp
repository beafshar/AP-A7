#include"Sale.h"

Sale::Sale(int _film_id, float _rate, float _price, int _user_id,
	int _publisher_id) {
	film_id = _film_id;
	rate = _rate;
	price = _price;
	user_id = _user_id;
	publisher_id = _publisher_id;
	paid_to_publisher = false;
}

void Sale::pay_to_publisher() {
	paid_to_publisher = true;
}

float Sale::calculate_publisher_share() {
	if (rate < LOW_RATE)
		return price * 0.8;
	if (rate >= LOW_RATE && rate < MEDIUM_RATE)
		return price * 0.9;
	if (rate >= MEDIUM_RATE)
		return price * 0.95;
}

bool Sale::if_paid_to_publisher() {
	return paid_to_publisher;
}

int Sale::get_customer_id() {
	return user_id;
}