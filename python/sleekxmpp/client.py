#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import logging
import sleekxmpp

# Python versions before 3.0 do not use UTF-8 encoding
# by default. To ensure that Unicode is handled properly
# throughout SleekXMPP, we will set the default encoding
# ourselves to UTF-8.
if sys.version_info < (3, 0):
    from sleekxmpp.util.misc_ops import setdefaultencoding
    setdefaultencoding('utf8')
else:
    raw_input = input

if __name__ == '__main__':

    # check arguments
    if len(sys.argv) < 5:
        print("Usage: python client.py <my-jid> <my-password> <my-text> <jid1>")
        sys.exit(1)

    # Setup logging.
    logging.basicConfig(level="DEBUG", format='%(levelname)-8s %(message)s')

    to  = sys.argv[4]
    msg = sys.argv[3]

    # create a new xmpp client
    xmpp = sleekxmpp.ClientXMPP(sys.argv[1], sys.argv[2])

    # define a handler function
    def onStart(ev):
        print("connected")
        xmpp.send_message(mto=to, mbody=msg, mtype='chat')
        xmpp.disconnect(wait=True)

    # add the function
    xmpp.add_event_handler("session_start", onStart)

    # connect to the XMPP server
    if xmpp.connect():
        xmpp.process(block=True)
        print("Disconnected")
    else:
        print("Unable to connect.")
