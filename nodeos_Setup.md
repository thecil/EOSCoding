# Nodeos EOSIO server Setup Guide

This file intend to describe the process i follow in order to setup/install a nodeos EOSIO server client on ubuntu 18.04.

## Getting Started

Step 1: Install binaries
* [EOSIO](https://github.com/EOSIO/eos/releases/). -EOSIO client
```
wget https://github.com/EOSIO/eos/releases/download/v1.8.6/eosio_1.8.6-1-ubuntu-18.04_amd64.deb
sudo apt install eosio_1.8.6-1-ubuntu-18.04_amd64.deb
```
* [CDT](https://github.com/EOSIO/eosio.cdt/releases/). -EOSIO cdt client

Step 2: Setup Directory
```
mkdir contracts
cd contracts
```

Step 4: Install CDT
```
wget https://github.com/EOSIO/eosio.cdt/releases/download/v1.7.0-rc1/eosio.cdt_1.7.0-rc1-ubuntu-18.04_amd64.deb
sudo apt install eosio.cdt_1.7.0-rc1-ubuntu-18.04_amd64.deb
```
