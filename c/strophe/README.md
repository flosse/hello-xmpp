# strophe

- Website: [strophe.im/libstrophe](http://strophe.im/libstrophe/)
- License: [MIT](https://github.com/strophe/libstrophe/raw/master/MIT-LICENSE.txt)
  and [GPLv3](https://github.com/strophe/libstrophe/raw/master/GPL-LICENSE.txt)
- Dependencies:
    - `expat` or `libxml2`
    - `libresolv` on UNIX systems

## Installation


    git clone https://github.com/flosse/hello-xmpp.git
    cd c/strophe/
    git clone https://github.com/strophe/libstrophe.git
    cd libstrophe
    ./bootstrap.sh
    ./configure
    make
    cd ..
    make

## Usage

    ./client myJID@server.tld myPass myMessage friend@example.org
