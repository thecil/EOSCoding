#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT dogcontract : public contract {
  public:
    using contract::contract;
    dogcontract(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds)
    {}
    /*
    ** Function insert the name and age of a dog with the dog_id.
    ** Owner can not be changed in this function.
    */
    ACTION insert(name owner, std::string dog_name, int age){
      //Require auth of the owner
      require_auth(owner);
      //Get the index of our table
      dog_index dogs(get_self(), get_self().value); //this is an scope
      //Execute the insert function. Specifying the dog_name and age,
      //payer of storage and a lambda function.
      dogs.emplace(owner, [&](auto& row){
        row.id = dogs.available_primary_key();
        row.dog_name = dog_name;
        row.age = age;
        row.owner = owner;
      });
      send_summary(owner, "dog inserted properly.")
    }//end ACTION insert

      /*
      ** Function delete dog by dog_id.
      ** Owner can not be changed in this function.
      */
      ACTION erase(int dog_id){
        //Get the index of our table
        dog_index dogs(get_self(), get_self().value); //this is an scope
        //Fetch the current data of our dog
        auto dog = dogs.get(dog_id, "Unable to fetch dog.");
        //Require auth of the owner
        require_auth(dog.owner);
        //Get the iterator to be able to find the row in the table
        auto iterator = dogs.find(dog_id);
        //Execute the erase function. Specifying the iterator,
        dogs.erase(iterator);
        send_summary(dog.owner, "dog erased properly.")
      }//end ACTION erase

      /*
      ** Function modifies the name and age of a dog with the dog_id.
      ** Owner can not be changed in this function.
      */
      ACTION modify(int dog_id, std::string dog_name, int age){
        //Get the index of our table
        dog_index dogs(get_self(), get_self().value);
        //Fetch the current data of our dog
        auto dog = dogs.get(dog_id, "Unable ot fetch dog.");
        //Require auth of the owner
        require_auth(dog.owner);
        //Get the iterator to be able to find and modify the row in the table
        auto iterator = dogs.find(dog_id);
        //Execute the modify function. Specifying the iterator,
        //payer of storage and a lambda function.
        dogs.modify(iterator, dog.owner, [&](auto& row){
        row.dog_name = dog_name;
        row.age = age;
        });
        send_summary(owner, "dog modified properly.")
      }//end ACTION modify

      /*
      ** Function remove all dogs by Owner.
      ** Owner can not be changed in this function.
      */
      ACTION removeall(name user){
        //Get the index of our table
        dog_index dogs(get_self(), get_self().value);
        //Fetch the current data of dogs by owner
        auto owner_index = dogs.get_index<"byowner"_n>();
        //Get the iterator to be able to find the row in the table
        auto iterator = owner_index.find(user.value);
        while(iterator != owner_index.end()){
          //delete row
          owner_index.erase(iterator);
          iterator = owner_index.find(user.value);
        }
        send_summary(user, "erased all dogs");
      }//end ACTION removeall
    private:
      //table struct dog
      TABLE dog{
      int id; //unique ID for index
      std::string dog_name;
      int age;
      name owner; //eos account name, owner of dogs
      //get primary key by ID variable
      uint64_t primary_key() const{return id;}
      //get dogs by owner index
      uint64_t by_owner() const{return owner.value;}
    };
      //inline action, notify to user if the action has been made sucessfully 
      void send_summary(name user, std::string message){
        action(
          permission_level{get_self(), "active"_n}, //contract name has permission level on active
          get_self(), //push to contract
          "notify"_n, //name of the action
          std::make_tuple(user, message)//actual data to send to
        ).send();
      };
      //define table type index
      typedef multi_index<"dogs"_n, dog, indexed_by<"byowner"_n, const_mem_fun<dog, uint64_t, &dog::by_owner>>> dog_index;

};
