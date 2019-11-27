# EOSIO CLI commands

Some stuffs to copy/paste in future.

## Compilation

```
eosio-cpp -abigen -o <OUTPUT> <SOURCE FILE>
```
An example of this command in action looks like this.
```
eosio-cpp -abigen -o dogcontract.wasm src/dogcontract.cpp
```
## Deployment
After compilation we can use our .wasm and .abi files to deploy our contract. To do this we need to use cleos. 
We use the "set contract" command to deploy code in eos. The general command we will use looks like this.
```
cleos set contract <ACCOUNT> <CONTRACT-DIR> <WASM-FILE> --abi <ABI-FILE> -p <ACCOUNT>@<PERMISSION>
```
Where the <ACCOUNT> is the account we are setting the contract to. 
<CONTRACT DIR> is where you need to put the absolute path to your contract directory. 
The path you copied after running "pwd" in your terminal. An example of this command in action looks like this.
```
cleos set contract dogcontract /Users/admin/Documents/eos-contracts/course-payable ./dogcontract.wasm --abi dogcontract.abi -p dogcontract@active
```

## Sending Actions to Contracts
After deployment we can execute our code by sending actions to the account where our contract is deployed. 
This is also done with cleos. The general command we will use looks like this.
```
cleos push action <CONTRACT-ACCOUNT> <ACTION-NAME> <ARGUMENTS> -p <ACCOUNT>@<PERMISSION>
```
An example of this command in action looks like this. Take a close look at how arguments are sent. They are sent as an array with the arguments in order. The entire array should always be wrapped in single quotes.
```
cleos push action dogcontract insert '["bob", "doggo", 100]' -p bob@active
```

## Getting Table Rows
We can fetch data from a table using cleos as well. The general command looks like this.
```
cleos get table <ACCOUNT> <SCOPE> <TABLE-NAME>
```
An example would be:
```
cleos get table bob bob dogs
```
