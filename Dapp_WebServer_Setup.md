# EOSIO Dapp WebServer Setup

Some stuffs to copy/paste in future for deployment of the webserver for dapps.

## Get Scatter
for linux is an .appImage
```
https://get-scatter.com/
```
After download, make file executable
```
sudo chmod +x linux-scatter-12.0.0-x86_64.AppImage
```
Start scatter
```
./linux-scatter-12.0.0-x86_64.AppImage
```

## Clone Dapp Template
Template from @filipmartinsson
```
git clone https://github.com/filipmartinsson/eos-dapp-template
```

## Install Python web server
if not installed
```
sudo apt-get install python
```
Navigate trough the template folder and start python web server
```
python3 -m http.server <PORT>
```

## Get chain_id for scatter connection
if curl not installed
```
sudo apt install curl
```
Get info about nodeos server connection (default port: 8888)
```
curl http://localhost:8888/v1/chain/get_info
```

