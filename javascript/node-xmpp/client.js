// import the library
var xmpp = require('node-xmpp');

// add an alias for the array of arguments
var argv = process.argv;

// check usage
if (argv.length < 6) {

  // print usage
  console.error(
    'Usage: node client.js <my-jid> ' +
    '<my-password> <my-text> <jid1> [jid2] ... [jidN]'
  );
  process.exit(1);
}

// create a new client instance
var cl = new xmpp.Client({ jid: argv[2],  password: argv[3] });

// as soon as the client is connected to the server
// the 'online' event will be emitted
cl.addListener('online', function(data) {

  // inform the user
  console.log(
    'Connected as ' + data.jid.user +
    '@' + data.jid.domain + '/' +
     data.jid.resource
  );

  // iterate over all JIDs
  argv.slice(5).forEach(function(to) {

    // create a new XML message with ltx (a xml library)
    var stanza = new xmpp.Element(
      'message', { to: to, type: 'chat' }
    ).c('body').t(argv[4])

    // stanza.toString() would result into something linke this:
    //
    // <message to='jid@example.org' type='chat>
    //   <body>The message text</body>
    // </message>

    // send the message
    cl.send(stanza);
  });

  // close the connection
  cl.end();

  // nodejs has nothing left to do and will exit
})

// if someting went wrong the 'error' event will be emitted
cl.addListener('error', function(e) {

  // log the error
  console.error(e);

  // close the connection
  cl.end();

  // and exit
  process.exit(1);
});
