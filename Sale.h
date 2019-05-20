#ifndef SALE_H
#define SALE_H

class Sale {

public:
	Sale(int _film_id, float _rate, float _price, int _user_id, int _publisher_id);
	void pay_to_publisher();
	float calculate_publisher_share();
	bool if_paid_to_publisher();
	int get_customer_id();

private:
	float rate;
	float price;
	int film_id;
	int user_id;
	int publisher_id;
	bool paid_to_publisher;

};

#endif 

