// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com

package ocsf.client;

import java.io.*;
import java.net.*;

/**
 * The <code> AbstractClient </code> contains all the methods necessary to set
 * up the client side of a client-server architecture. When a client is thus
 * connected to the server, the two programs can then exchange
 * <code> Object </code> instances.
 * AbstractClient 包含所有設定 client 端所需要的方法。當 client 連接 server 時，兩個
 * 程式可以交換 Object 。
 * 
 * <p>
 * Method <code> handleMessageFromServer </code> must be defined by a concrete
 * subclass. Several other hook methods may also be overriden.
 * handleMessageFromServer 方法必須被具體的子類別定義。而其他幾個 hook 也可能被覆寫。
 * 
 * <p>
 * Several public service methods are provided to application that use this
 * framework.
 * 有幾個公共服務方法提供給使用這個框架的應用程式用。
 * 
 * <p>
 * Project Name: OCSF (Object Client-Server Framework)
 * <p>
 * 
 * @author Dr. Robert Lagani&egrave;re
 * @author Dr. Timothy C. Lethbridge
 * @author Fran&ccedil;ois B&eacutel;langer
 * @author Paul Holden
 * @version February 2001 (2.12)
 */
public abstract class AbstractClient implements Runnable {

	// INSTANCE VARIABLES ***********************************************

	/**
	 * Sockets are used in the operating system as channels of communication
	 * between two processes.
	 * Sockets 是作業系統中兩個程序溝通使用的管道。
	 * 
	 * @see java.net.Socket
	 */
	private Socket				clientSocket;

	/**
	 * The stream to handle data going to the server.
	 * 用來處理傳送到 server 的資料串流。
	 */
	private ObjectOutputStream	output;

	/**
	 * The stream to handle data from the server.
	 * 用來處理來自 server 的資料串流。
	 */
	private ObjectInputStream	input;

	/**
	 * The thread created to read data from the server.
	 * 用來讀取來自 server 資料的執行緒。
	 */
	private Thread				clientReader;

	/**
	 * Indicates if the thread is ready to stop. Needed so that the loop in the
	 * run method knows when to stop waiting for incoming messages.
	 * 用來表示執行緒是否準備停止，以讓在迴圈中執行的方法得知何時該停止等待傳入的訊息。
	 */
	private boolean				readyToStop	= false;

	/**
	 * The server's host name.
	 * 伺服器的主機名稱。
	 */
	private String				host;

	/**
	 * The port number.
	 * 埠號。
	 */
	private int					port;

	// CONSTRUCTORS *****************************************************

	/**
	 * Constructs the client.
	 * 
	 * @param host
	 *            the server's host name.
	 * @param port
	 *            the port number.
	 */
	public AbstractClient(String host, int port) {
		// Initialize variables
		this.host = host;
		this.port = port;
	}

	// INSTANCE METHODS *************************************************

	/**
	 * Opens the connection with the server. If the connection is already
	 * opened, this call has no effect.
	 * 開啟與 server 的連接。若連線已開始，則此函式的呼叫不會有影響。
	 * 
	 * @exception IOException
	 *                if an I/O error occurs when opening. 若傳送時發生 I/O 錯誤。
	 */
	final public void openConnection() throws IOException {
		// Do not do anything if the connection is already open
		// 若連線已開始則不做任何事直接回傳。
		if (isConnected())
			return;

		// Create the sockets and the data streams
		// 建立 socket 與資料傳輸串流。
		try {
			clientSocket = new Socket(host, port);
			output = new ObjectOutputStream(clientSocket.getOutputStream());
			input = new ObjectInputStream(clientSocket.getInputStream());
		} catch (IOException ex)
		// All three of the above must be closed when there is a failure
		// to create any of them
		// 若有任何建立失敗的情況，必須將上述三者一起關閉。
		{
			try {
				closeAll();
			} catch (Exception exc) {
			}

			throw ex; // Rethrow the exception. 拋出例外情況。
		}

		clientReader = new Thread(this); // Create the data reader thread 創建讀取資料執行緒。
		readyToStop = false;
		clientReader.start(); // Start the thread 開始執行緒。
	}

	/**
	 * Sends an object to the server. This is the only way that methods should
	 * communicate with the server.
	 * 傳送物件給 server。這應該要是唯一與 server 溝通的方法。
	 * 
	 * @param msg
	 *            The message to be sent. 要被傳送的訊息。
	 * @exception IOException
	 *                if an I/O error occurs when sending 若傳送時發生 I/O 錯誤。
	 */
	final public void sendToServer(Object msg) throws IOException {
		if (clientSocket == null || output == null)
			throw new SocketException("socket does not exist");

		output.writeObject(msg);
	}

	/**
	 * Reset the object output stream so we can use the same
	 * buffer repeatedly. This would not normally be used, but is necessary
     * in some circumstances when Java refuses to send data that it thinks has been sent.
	 * 重置物件輸出串流以讓我們能重複使用同一緩衝區。通常不會使用此方法，但在某些情況下，當 Java
	 * 認為發送過數據而拒絕再發送時，這方法是必要的。
	 */
	final public void forceResetAfterSend() throws IOException {
      output.reset();
	}

	/**
	 * Closes the connection to the server.
	 * 關閉與 server 的連結。
	 * 
	 * @exception IOException
	 *                if an I/O error occurs when closing. 若傳送時發生 I/O 錯誤。
	 */
	final public void closeConnection() throws IOException {
		// Prevent the thread from looping any more
		// 防止執行緒再繼續迴圈。
		readyToStop = true;

		try {
			closeAll();
		} finally {
			// Call the hook method 呼叫 hook method。
			connectionClosed();
		}
	}

	// ACCESSING METHODS ------------------------------------------------

	/**
	 * @return true if the client is connected. 若已連接則回傳 true。
	 */
	final public boolean isConnected() {
		return clientReader != null && clientReader.isAlive();
	}

	/**
	 * @return the port number. 回傳埠號。
	 */
	final public int getPort() {
		return port;
	}

	/**
	 * Sets the server port number for the next connection. The change in port
	 * only takes effect at the time of the next call to openConnection().
	 * 設定下次連接的 server port。此改變只會在下次呼叫 openConnection 時生效。
	 * 
	 * @param port
	 *            the port number.
	 */
	final public void setPort(int port) {
		this.port = port;
	}

	/**
	 * @return the host name. 回傳主機名稱。
	 */
	final public String getHost() {
		return host;
	}

	/**
	 * Sets the server host for the next connection. The change in host only
	 * takes effect at the time of the next call to openConnection().
	 * 設定下次連接的 server host。此改變只會在下次呼叫 openConnection 時生效。 *
	 * 
	 * @param host
	 *             the host name.
	 */
	final public void setHost(String host) {
		this.host = host;
	}

	/**
	 * returns the client's description.
	 * 回傳客戶端的描述。
	 * 
	 * @return the client's Inet address. 回傳客戶端的 Inet 地址。
	 */
	final public InetAddress getInetAddress() {
		return clientSocket.getInetAddress();
	}

	// RUN METHOD -------------------------------------------------------

	/**
	 * Waits for messages from the server. When each arrives, a call is made to
	 * <code>handleMessageFromServer()</code>. Not to be explicitly called.
	 * 等待來自 server 的訊息。每當訊息抵達時，會呼叫 handleMessageFromServer 方法。
	 * 此方法不需明確呼叫。
	 */
	final public void run() {
		connectionEstablished();

		// The message from the server 從 server 來的訊息。
		Object msg;

		// Loop waiting for data 等待資料的迴圈。

		try {
			while (!readyToStop) {
				// Get data from Server and send it to the handler
				// The thread waits indefinitely at the following
				// statement until something is received from the server
				// 從 server 獲得資料並傳送給處理器。
				// 該執行緒將無限期地等待直到從 server 收到某些內容。
				msg = input.readObject();

				// Concrete subclasses do what they want with the
				// msg by implementing the following method
				// 具體子類別藉由執行以下方法，對訊息進行處理。
				handleMessageFromServer(msg);
			}
		} catch (Exception exception) {
			if (!readyToStop) {
				try {
					closeAll();
				} catch (Exception ex) {
				}

				connectionException(exception);
			}
		} finally {
			clientReader = null;
		}
	}

	// METHODS DESIGNED TO BE OVERRIDDEN BY CONCRETE SUBCLASSES ---------

	/**
	 * Hook method called after the connection has been closed. The default
	 * implementation does nothing. The method may be overridden by subclasses to
	 * perform special processing such as cleaning up and terminating, or
	 * attempting to reconnect.
	 * 連接關閉後呼叫的 Hook 函式。預設不執行動作。此函式可被子類別覆寫以執行特殊處理，如
	 * 清理、中止，或嘗試重新連接。
	 */
	protected void connectionClosed() {
	}

	/**
	 * Hook method called each time an exception is thrown by the client's
	 * thread that is waiting for messages from the server. The method may be
	 * overridden by subclasses.
	 * 每當 client 的執行緒等待 server 訊息中拋出例外狀況時呼叫的 Hook 函式。此函式
	 * 可被子類別覆寫。
	 * 
	 * @param exception
	 *            the exception raised. 發生例外狀況。
	 */
	protected void connectionException(Exception exception) {
	}

	/**
	 * Hook method called after a connection has been established. The default
	 * implementation does nothing. It may be overridden by subclasses to do
	 * anything they wish.
	 * 在連接建立後呼叫的 Hook 函式。預設不執行動作。此函式可被子類別覆寫以執行想做的事。
	 */
	protected void connectionEstablished() {
	}

	/**
	 * Handles a message sent from the server to this client. This MUST be
	 * implemented by subclasses, who should respond to messages.
	 * 處理從 server 傳到此 client 的訊息。此函式必須由負責回應訊息的子類別實作。
	 * 
	 * @param msg
	 *            the message sent. 傳送的訊息。
	 */
	protected abstract void handleMessageFromServer(Object msg);

	// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

	/**
	 * Closes all aspects of the connection to the server.
	 * 關閉所有和 server 的任何連接
	 * 
	 * @exception IOException
	 *                if an I/O error occurs when closing. 若關閉時發生 I/O 錯誤。
	 */
	private void closeAll() throws IOException {
		try {
			// Close the socket 關閉 socket
			if (clientSocket != null)
				clientSocket.close();

			// Close the output stream 關閉輸出串流
			if (output != null)
				output.close();

			// Close the input stream 關閉輸入串流
			if (input != null)
				input.close();
		} finally {
			// Set the streams and the sockets to NULL no matter what
			// Doing so allows, but does not require, any finalizers
			// of these objects to reclaim system resources if and
			// when they are garbage collected.
			// 將串流及 socket 設為空。這麼做可以讓物件的 finalizers 在垃圾
			// 回收時重新獲取系統資源，但並不強制執行。
			output = null;
			input = null;
			clientSocket = null;
		}
	}
}
// end of AbstractClient class