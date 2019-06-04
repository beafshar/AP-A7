#include"Filter.h"
#include"Movie.h"

Filter::Filter(std::string name) {
	if(name.compare("")==0){
	 director = std::to_string(NOT_VALUED);
   std::cout<<"nooooot"<<std::endl;
 }
	director = name;
}

bool Filter::filter_by_director(Movie* film) {
	if (director == std::to_string(NOT_VALUED)){
    std::cout<<"first"<<std::endl;
		return true;
  }
	if (film->get_director() == director){
  std::cout<<"second"<<std::endl;
		return true;
  }
	else{
  std::cout<<"third"<<"  "<<film->get_director()<<"  "<<director<<std::endl;
		return false;
  }
}
