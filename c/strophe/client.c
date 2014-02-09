/* client.c
 * This is a modified version of:
 * https://raw2.github.com/strophe/libstrophe/master/examples/basic.c
*/

#include <stdio.h>
#include <strophe.h>

/* quick n dirty global vars*/
char *msg, *to;

/* define a handler for connection events */
void conn_handler(xmpp_conn_t * const conn, const xmpp_conn_event_t status,
                  const int error, xmpp_stream_error_t * const stream_error,
                  void * const userdata)
{
  xmpp_ctx_t *ctx = (xmpp_ctx_t *)userdata;
  xmpp_stanza_t *message, *body, *text;

  if (status == XMPP_CONN_CONNECT) {

    fprintf(stderr, "DEBUG: connected\n");

    /* create message stanza */
    message = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(message, "message");
    xmpp_stanza_set_type(message, "chat");
    xmpp_stanza_set_attribute(message, "to", to);

    /* create the body */
    body = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(body, "body");

    /* create text */
    text = xmpp_stanza_new(ctx);
    xmpp_stanza_set_text(text, msg);
    xmpp_stanza_add_child(body, text);

    /* we can release the text since it belongs to body now */
    xmpp_stanza_release(text);

    /* append body stanza */
    xmpp_stanza_add_child(message, body);

    //* we can release the body stanza since it belongs to message now */
    xmpp_stanza_release(body);

    /* send out the stanza */
    xmpp_send(conn, message);

    /* release the message stanza */
    xmpp_stanza_release(message);

    /* disconnect */
    xmpp_disconnect(conn);
  }
  else {
    fprintf(stderr, "DEBUG: disconnected\n");
    xmpp_stop(ctx);
  }
}

int main(int argc, char **argv)
{
  xmpp_ctx_t  *ctx;
  xmpp_conn_t *conn;
  xmpp_log_t  *log;

  char *jid, *pass, *host;

  /* take a jid, password, message text and target JID on the command line */
  if (argc < 5 ) {
    fprintf(stderr, "Usage: client <my-jid> <my-password> <my-text> <jid1> [<host>]\n\n");
    return 1;
  }

  jid   = argv[1];
  pass  = argv[2];
  msg   = argv[3];
  to    = argv[4];
  host  = NULL;

  if (argc == 6)
      host = argv[5];

  /* init library */
  xmpp_initialize();

  /* create a context */
  log = xmpp_get_default_logger(XMPP_LEVEL_DEBUG); /* pass NULL instead to silence output */
  ctx = xmpp_ctx_new(NULL, log);

  /* create a connection */
  conn = xmpp_conn_new(ctx);

  /* setup authentication information */
  xmpp_conn_set_jid(conn, jid);
  xmpp_conn_set_pass(conn, pass);

  /* initiate connection */
  xmpp_connect_client(conn, host, 0, conn_handler, ctx);

  /* enter the event loop -
     our connect handler will trigger an exit */
  xmpp_run(ctx);

  /* release our connection and context */
  xmpp_conn_release(conn);
  xmpp_ctx_free(ctx);

  /* final shutdown of the library */
  xmpp_shutdown();

  return 0;
}
