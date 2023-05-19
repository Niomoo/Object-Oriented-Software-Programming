// This file contains material supporting section 3.8 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package ocsf.server;

import java.net.*;
import java.util.*;
import java.io.*;

/**
 * The <code> AbstractServer </code> class maintains a thread that waits
 * for connection attempts from clients. When a connection attempt occurs
 * it creates a new <code> ConnectionToClient </code> instance which
 * runs as a thread. When a client is thus connected to the
 * server, the two programs can then exchange <code> Object </code>
 * instances.<p>
 * AbstractServer 類別維護一個執行緒，該執行緒用來等待來自 clients 的連接嘗試。
 * 當嘗試連接時，此類別會產生一個新的 ConnectionToClient 實例作為執行緒運行。
 * 如此一來，當 client 連接到 server 後，兩個程式就可以互相交換物件實例。
 *
 * Method <code> handleMessageFromClient </code> must be defined by
 * a concrete subclass. Several other hook methods may also be
 * overriden.<p>
 * handeleMessageFromClient 須被具體子類別定義。而其他幾個 hook 也可能被覆寫。
 *
 * Several public service methods are provided to applications that use
 * this framework, and several hook methods are also available<p>
 * 有幾個公共服務方法提供給使用這個框架的應用程式用，而一些 hook 方法也是可取得的。
 *
 * Project Name: OCSF (Object Client-Server Framework)<p>
 *
 * @author Dr Robert Lagani&egrave;re
 * @author Dr Timothy C. Lethbridge
 * @author Fran&ccedil;ois B&eacute;langer
 * @author Paul Holden
 * @version February 2001 (2.12)
 * @see ocsf.server.ConnectionToClient
 */
public abstract class AbstractServer implements Runnable
{
  // INSTANCE VARIABLES *********************************************

  /**
   * The server socket: listens for clients who want to connect.
   * 用來監聽想連接的 clients
   */
  private ServerSocket serverSocket = null;

  /**
   * The connection listener thread.
   * 連線監聽執行緒。
   */
  private Thread connectionListener;

  /**
   * The port number
   * 埠號。
   */
  private int port;

  /**
   * The server timeout while for accepting connections.
   * After timing out, the server will check to see if a command to
   * stop the server has been issued; if not it will resume accepting
   * connections.
   * Set to half a second by default.
   * 接受連線的超時設定。
   * 在超時後，server 會檢查是否發生停止 server 的指令，否則會繼續接受連結。
   * 預設超時時間為 0.5 秒。
   */
  private int timeout = 500;

  /**
   * The maximum queue length; i.e. the maximum number of clients that
   * can be waiting to connect.
   * Set to 10 by default.
   * 可以等待連接的 clients 數量最大值。預設為 10。
   */
  private int backlog = 10;

  /**
   * The thread group associated with client threads. Each member of the
   * thread group is a <code> ConnectionToClient </code>.
   * 與 client 連結的執行緒群組。執行緒群組的每個成員為 ConnectionToClient 類別。
   */
  private ThreadGroup clientThreadGroup;

  /**
   * Indicates if the listening thread is ready to stop.  Set to
   * false by default.
   * 表示監聽的執行緒是否準備停止。預設為 false。
   */
  private boolean readyToStop = false;


// CONSTRUCTOR ******************************************************

  /**
   * Constructs a new server.
   *
   * @param port the port number on which to listen. 監聽埠號。
   */
  public AbstractServer(int port)
  {
    this.port = port;

    this.clientThreadGroup =
      new ThreadGroup("ConnectionToClient threads")
      {
        // All uncaught exceptions in connection threads will
        // be sent to the clientException callback method.
        // 所有連線執行緒中未捕獲的異常情況會被傳送至 clientException 
        // 回呼函式。
        public void uncaughtException(
          Thread thread, Throwable exception)
        {
          clientException((ConnectionToClient)thread, exception);
        }
      };
  }


// INSTANCE METHODS *************************************************

  /**
   * Begins the thread that waits for new clients.
   * If the server is already in listening mode, this
   * call has no effect.
   * 開始等待新 client 的執行緒。
   * 若 server 已經在監聽模式，此呼叫不會有任何影響。 
   *
   * @exception IOException if an I/O error occurs
   * when creating the server socket. 
   * 若創造 server socket 時有發生 I/O 例外狀況。
   */
  final public void listen() throws IOException
  {
    if (!isListening())
    {
      if (serverSocket == null)
      {
        serverSocket = new ServerSocket(getPort(), backlog);
      }

      serverSocket.setSoTimeout(timeout);
      readyToStop = false;
      connectionListener = new Thread(this);
      connectionListener.start();
    }
  }

  /**
   * Causes the server to stop accepting new connections.
   * 使 server 停止接受新的連線。
   */
  final public void stopListening()
  {
    readyToStop = true;
  }

  /**
   * Closes the server socket and the connections with all clients.
   * Any exception thrown while closing a client is ignored.
   * If one wishes to catch these exceptions, then clients
   * should be individually closed before calling this method.
   * The method also stops listening if this thread is running.
   * If the server is already closed, this
   * call has no effect.
   * 關閉 server socket 與所有 clients 的連接。
   * 任何拋出的例外會被忽略。若想得知這些例外狀況，在呼叫此方法前，client 
   * 應先獨立關閉。若執行緒仍在運作，此方法也能停止監聽。若 server 已經被
   * 關閉，則此呼叫不會有任何影響。
   *
   * @exception IOException if an I/O error occurs while
   * closing the server socket. 
   * 若關閉 server socket 時有發生 I/O 例外狀況。
   */
  final synchronized public void close() throws IOException
  {
    if (serverSocket == null)
      return;
      stopListening();
    try
    {
      serverSocket.close();
    }
    finally
    {
      // Close the client sockets of the already connected clients
      // 關閉已經連接的 client sockets。
      Thread[] clientThreadList = getClientConnections();
      for (int i=0; i<clientThreadList.length; i++)
      {
         try
         {
           ((ConnectionToClient)clientThreadList[i]).close();
         }
         // Ignore all exceptions when closing clients.
         // 關閉 clients 時忽略所有異常狀況。
         catch(Exception ex) {}
      }
      serverSocket = null;
      serverClosed();
    }
  }

  /**
   * Sends a message to every client connected to the server.
   * This is merely a utility; a subclass may want to do some checks
   * before actually sending messages to all clients.  This method
   * can be overridden, but if so it should still perform the general
   * function of sending to all clients, perhaps after some kind
   * of filtering is done. Any exception thrown while
   * sending the message to a particular client is ignored.
   * 向所有連接此 server 的 client 發送訊息。
   * 這只是一個工具，子類別在實際發送訊息給所有 clients 前可能要做一些檢查。
   * 這個方法可以被覆寫，但這樣做仍然須向所有 clients 運作一般的功能，也許是
   * 執行某種篩選後再進行。在向特定 client 發送的訊息時引發的異常都會被忽略。
   *
   * @param msg   Object The message to be sent 發送的訊息物件
   */
  public void sendToAllClients(Object msg)
  {
    Thread[] clientThreadList = getClientConnections();

    for (int i=0; i<clientThreadList.length; i++)
    {
      try
      {
        ((ConnectionToClient)clientThreadList[i]).sendToClient(msg);
      }
      catch (Exception ex) {}
    }
  }


// ACCESSING METHODS ------------------------------------------------

  /**
   * Returns true if the server is ready to accept new clients.
   * 若 server 準備好接受新的 clients 時回傳 true。
   *
   * @return true if the server is listening. 回傳 server 是否正在監聽。
   */
  final public boolean isListening()
  {
    return (connectionListener != null);
  }

  /**
   * Returns an array containing the existing
   * client connections. This can be used by
   * concrete subclasses to implement messages that do something with
   * each connection (e.g. kill it, send a message to it etc.).
   * Remember that after this array is obtained, some clients
   * in this might disconnect. New clients can also connect,
   * these later will not appear in the array.
   * 回傳一個包含目前連接的 client 的陣列。
   * 此方法可以被具體子類別執行每個連線訊息的動作時使用，如關閉、發送訊息等。
   * 要記得在獲得該陣列後，陣列內的 clients 可能會離線，也可能有新的 client
   * 加入但尚未出現在陣列之中。
   *
   * @return an array of <code>Thread</code> containing
   *         <code>ConnectionToClient</code> instances.
   * 包含 ConnectionToClient 實力的陣列。
   */
  synchronized final public Thread[] getClientConnections()
  {
    Thread[] clientThreadList = new
      Thread[clientThreadGroup.activeCount()];

    clientThreadGroup.enumerate(clientThreadList);

    return clientThreadList;
  }

  /**
   * Counts the number of clients currently connected.
   * 目前連接的 clients 數量。
   *
   * @return the number of clients currently connected.
   */
  final public int getNumberOfClients()
  {
    return clientThreadGroup.activeCount();
  }

  /**
   * Returns the port number.
   * 回傳埠號。
   *
   * @return the port number.
   */
  final public int getPort()
  {
    return port;
  }

  /**
   * Sets the port number for the next connection.
   * The server must be closed and restarted for the port
   * change to be in effect.
   * 設定下次連接的 port。server 必須關閉並重新啟動， port 改動才會生效。
   * @param port the port number.
   */
  final public void setPort(int port)
  {
    this.port = port;
  }

  /**
   * Sets the timeout time when accepting connections.
   * The default is half a second. This means that stopping the
   * server may take up to timeout duration to actually stop.
   * The server must be stopped and restarted for the timeout
   * change to be effective.
   * 設定接收連線的超時時間。預設為 0.5 秒。
   * 這代表 server 可能會花到設定的超時時間才會真正停止。
   * server 必須停止並重新啟動以讓超時的改動生效。
   *
   * @param timeout the timeout time in ms. 超時的時間，單位為毫秒
   */
  final public void setTimeout(int timeout)
  {
    this.timeout = timeout;
  }

  /**
   * Sets the maximum number of waiting connections accepted by the
   * operating system. The default is 20.
   * The server must be closed and restarted for the backlog
   * change to be in effect.
   *
   * @param backlog the maximum number of connections.
   */
  final public void setBacklog(int backlog)
  {
    this.backlog = backlog;
  }

// RUN METHOD -------------------------------------------------------

  /**
   * Runs the listening thread that allows clients to connect.
   * Not to be called.
   */
  final public void run()
  {
    // call the hook method to notify that the server is starting
    serverStarted();

    try
    {
      // Repeatedly waits for a new client connection, accepts it, and
      // starts a new thread to handle data exchange.
      while(!readyToStop)
      {
        try
        {
          // Wait here for new connection attempts, or a timeout
          Socket clientSocket = serverSocket.accept();

          // When a client is accepted, create a thread to handle
          // the data exchange, then add it to thread group

          synchronized(this)
          {
            ConnectionToClient c = new ConnectionToClient(
              this.clientThreadGroup, clientSocket, this);
          }
        }
        catch (InterruptedIOException exception)
        {
          // This will be thrown when a timeout occurs.
          // The server will continue to listen if not ready to stop.
        }
      }

      // call the hook method to notify that the server has stopped
      serverStopped();
    }
    catch (IOException exception)
    {
      if (!readyToStop)
      {
        // Closing the socket must have thrown a SocketException
        listeningException(exception);
      }
      else
      {
        serverStopped();
      }
    }
    finally
    {
      readyToStop = true;
      connectionListener = null;
    }
  }


// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

  /**
   * Hook method called each time a new client connection is
   * accepted. The default implementation does nothing.
   * @param client the connection connected to the client.
   */
  protected void clientConnected(ConnectionToClient client) {}

  /**
   * Hook method called each time a client disconnects.
   * The default implementation does nothing. The method
   * may be overridden by subclasses but should remains synchronized.
   *
   * @param client the connection with the client.
   */
  synchronized protected void clientDisconnected(
    ConnectionToClient client) {}

  /**
   * Hook method called each time an exception is thrown in a
   * ConnectionToClient thread.
   * The method may be overridden by subclasses but should remains
   * synchronized.
   *
   * @param client the client that raised the exception.
   * @param Throwable the exception thrown.
   */
  synchronized protected void clientException(
    ConnectionToClient client, Throwable exception) {}

  /**
   * Hook method called when the server stops accepting
   * connections because an exception has been raised.
   * The default implementation does nothing.
   * This method may be overriden by subclasses.
   *
   * @param exception the exception raised.
   */
  protected void listeningException(Throwable exception) {}

  /**
   * Hook method called when the server starts listening for
   * connections.  The default implementation does nothing.
   * The method may be overridden by subclasses.
   */
  protected void serverStarted() {}

  /**
   * Hook method called when the server stops accepting
   * connections.  The default implementation
   * does nothing. This method may be overriden by subclasses.
   */
  protected void serverStopped() {}

  /**
   * Hook method called when the server is clased.
   * The default implementation does nothing. This method may be
   * overriden by subclasses. When the server is closed while still
   * listening, serverStopped() will also be called.
   */
  protected void serverClosed() {}

  /**
   * Handles a command sent from one client to the server.
   * This MUST be implemented by subclasses, who should respond to
   * messages.
   * This method is called by a synchronized method so it is also
   * implcitly synchronized.
   *
   * @param msg   the message sent.
   * @param client the connection connected to the client that
   *  sent the message.
   */
  protected abstract void handleMessageFromClient(
    Object msg, ConnectionToClient client);


// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

  /**
   * Receives a command sent from the client to the server.
   * Called by the run method of <code>ConnectionToClient</code>
   * instances that are watching for messages coming from the server
   * This method is synchronized to ensure that whatever effects it has
   * do not conflict with work being done by other threads. The method
   * simply calls the <code>handleMessageFromClient</code> slot method.
   *
   * @param msg   the message sent.
   * @param client the connection connected to the client that
   *  sent the message.
   */
  final synchronized void receiveMessageFromClient(
    Object msg, ConnectionToClient client)
  {
    this.handleMessageFromClient(msg, client);
  }
}
// End of AbstractServer Class
