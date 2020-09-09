# EOSIO CLI commands

Snippets to copy/paste in future for CLEOS node on LINUX.

## Creating wallet

creating a wallet with personal name, will print password in console, KEEP PASSWORD SAFE.
```
cleos wallet create -n [namehere] --to-console
```
## Creaing eosio keys to later import on a wallet.
creating keys (public and private) to used on a wallet. Can create has many has u need. KEEP PRIVATE KEYS SAFE.
```
cleos create key --to-console
```
After, private keys must be imported into a wallet.
IMPORTANT: private keys to create account must be imported into the wallet. THIS IS A PUBLIC PRIVATE KEY, CAN BE FOUND ON INTERNET.
5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
```
cleos wallet import
```
paste private key.
to check private keys on a wallet
```
cleos wallet private_keys
```
it will show all public and private keys managed by the wallet.

## Creating an account inside a wallet.
After properly wallet created and imported with eosio private keys (to create accounts) and his own private key.
```
cleos create account eosio [accountNameHere] [ownerKey] [activeKey]
```
get account info
```
cleos get account [accountNameHere]
```
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
  
## Set permissions
this is need it to be able to push actions into a contract
```
 cleos set account permission [account] active --add-code 
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
## Payable Funtions/Token Creation setup
Clone eosio.contract rules to deploy it on an account

```
git clone https://github.com/EOSIO/eosio.contracts --branch v1.7.0 --single-branch
```
navigate to eosio.token folder, must compile the contract
(-I include means for include the folder that file is located)

```
eosio-cpp -I include --abigen -o eosio.token.wasm ./src/eosio.token.cpp
```
Create a eosio.token account to issue the tokens

```
cleos create account eosio eosio.token [owner key] [active key]
```
Deploy contract to account

```
cleos set contract eosio.token ~/contracts/eosio.contracts/contracts/eosio.token ./eosio.token.wasm --abi eosio.token.abi -p eosio.token@active
```

## Token Creation
Create token on account

```
cleos push action eosio.token create '["accountNameHere","XXXXXX NAMECOINHERE"]' -p <account>@active 
```

Issue the tokens to an account

```
cleos push action eosio.token issue '["accountNameHere","XXXXXX NAMECOINHERE","WriteAMemoHere"]' -p <account>@active 
```

Check account balance
```
cleos get table eosio.token <accountNameHere> accounts
```

Send token from issuer to others
```
cleos transfer [OPTIONS] sender recipient amount [memo] -p <account>@active

Ex: cleos transfer bob inline "20 DOGCOIN" "get some coins!!" -p bob@active
```
