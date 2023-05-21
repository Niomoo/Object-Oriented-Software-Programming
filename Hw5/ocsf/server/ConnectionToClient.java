// This file contains material supporting section 3.8 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com

package ocsf.server;

import java.io.*;
import java.net.*;
import java.util.HashMap;

/**
 * An instance of this class is created by the server when a client connects. It
 * accepts messages coming from the client and is responsible for sending data
 * to the client since the socket is private to this class. The AbstractServer
 * contains a set of instances of this class and is responsible for adding and
 * deleting them.
 * 當一個 client 連接時，server 將創造此類別的實例。其接受來自 client 的訊息並負責傳送資料
 * 給 client，因爲 socket 對此類別是私有的。AbstractServer 包含此類別的一組實力，並負責新
 * 增及刪除他們。
 * <p>
 * Project Name: OCSF (Object Client-Server Framework)
 * <p>
 * 
 * @author Dr Robert Lagani&egrave;re
 * @author Dr Timothy C. Lethbridge
 * @author Fran&ccedil;ois B&eacute;langer
 * @author Paul Holden
 * @version February 2001 (2.12)
 */
public class ConnectionToClient extends Thread {
	// INSTANCE VARIABLES ***********************************************

	/**
	 * A reference to the Server that created this instance.
	 * 指向創造此實例的 server 的參考。
	 */
	private AbstractServer		server;

	/**
	 * Sockets are used in the operating system as channels of communication
	 * between two processes.
	 * Socket 在作業系統中是兩個程序間用來溝通的管道。
	 * 
	 * @see java.net.Socket
	 */
	private Socket				clientSocket;

	/**
	 * Stream used to read from the client.
	 * 從 client 讀取的串流。
	 */
	private ObjectInputStream	input;

	/**
	 * Stream used to write to the client.
	 * 寫入到 client 的串流。
	 */
	private ObjectOutputStream	output;

	/**
	 * Indicates if the thread is ready to stop. Set to true when closing of the
	 * connection is initiated.
	 * 表示執行緒是否準備好停止。當初始化關閉連接時設定為 true。
	 */
	private boolean				readyToStop;

	/**
	 * Map to save information about the client such as its login ID. The
	 * initial size of the map is small since it is not expected that concrete
	 * servers will want to store many different types of information about each
	 * client. Used by the setInfo and getInfo methods.
	 * 保存如登入帳號等有關 client 資訊的表。表的初始大小很小，因為實體 server 不會預期要儲存
	 * 關於每個 client 許多不同類型的資訊。這會被 setInfo 和 getInfo 方法使用。
	 */
	private HashMap				savedInfo	= new HashMap(10);

	// CONSTRUCTORS *****************************************************

	/**
	 * Constructs a new connection to a client. 建立一個與 client 的新連線。
	 * 
	 * @param group
	 *            the thread groupSystem.out.println("Client at "+ client +
	 *            "connected"); that contains the connections.
	 * @param clientSocket
	 *            contains the client's socket.
	 * @param server
	 *            a reference to the server that created this instance
	 * @exception IOException
	 *                if an I/O error occur when creating the connection.
	 */
	ConnectionToClient(ThreadGroup group, Socket clientSocket, AbstractServer server) throws IOException {
		super(group, (Runnable) null);
		// Initialize variables 初始化變數
		this.clientSocket = clientSocket;
		this.server = server;

		clientSocket.setSoTimeout(0); // make sure timeout is infinite 確保超時是無限的

		// Initialize the objects streams 初始化物件串流
		try {
			input = new ObjectInputStream(clientSocket.getInputStream());
			output = new ObjectOutputStream(clientSocket.getOutputStream());
		} catch (IOException ex) {
			try {
				closeAll();
			} catch (Exception exc) {
			}

			throw ex; // Rethrow the exception. 重新拋出例外情況
		}

		readyToStop = false;
		start(); // Start the thread waits for data from the socket 開始等待 socket 資料的執行緒 
	}

	// INSTANCE METHODS *************************************************

	/**
	 * Sends an object to the client. 傳送物件給 client。
	 * 
	 * @param msg
	 *            the message to be sent.
	 * @exception IOException
	 *                if an I/O error occur when sending the message.
	 */
	final public void sendToClient(Object msg) throws IOException {
		if (clientSocket == null || output == null)
			throw new SocketException("socket does not exist");

		output.writeObject(msg);
	}

	/**
	 * Reset the output stream so we can use the same
	 * buffer repeatedly. This would not normally be used, but is necessary
     * in some circumstances when Java refuses to send data that it thinks has been sent.
	 * 重置輸出串流以讓我們可以重複使用相同的緩衝器。通常不會使用此方法，但在某些情況下，當 Java
	 * 認為發送過數據而拒絕再發送時，這方法是必要的。
	 */
	final public void forceResetAfterSend() throws IOException {
      output.reset();
	}

	/**
	 * Closes the client. If the connection is already closed, this call has no effect.
	 * 關閉 client。若連線已經關閉，此呼叫不會產生任何影響。
	 * 
	 * @exception IOException
	 *                if an error occurs when closing the socket.
	 */
	final public void close() throws IOException {
		readyToStop = true; // Set the flag that tells the thread to stop

		try {
			closeAll();
		} finally {
			server.clientDisconnected(this);
		}
	}

	// ACCESSING METHODS ------------------------------------------------

	/**
	 * Returns the address of the client. 回傳 client 的位址。
	 * 
	 * @return the client's Internet address.
	 */
	final public InetAddress getInetAddress() {
		return clientSocket == null ? null : clientSocket.getInetAddress();
	}

	/**
	 * Returns a string representation of the client. 回傳以字串表示的 client。
	 * 
	 * @return the client's description.
	 */
	public String toString() {
		return clientSocket == null ? null : clientSocket.getInetAddress().getHostName() + " ("
				+ clientSocket.getInetAddress().getHostAddress() + ")";
	}

	/**
	 * Saves arbitrary information about this client. Designed to be used by
	 * concrete subclasses of AbstractServer. Based on a hash map.
	 * 保存關於此 client 的任意資訊。設計被 AbstractServer 的實體子類別使用。
	 * 基於雜湊表。
	 * 
	 * @param infoType
	 *            identifies the type of information 辨識資訊的類別。
	 * @param info
	 *            the information itself. 資訊內容。
	 */
	public void setInfo(String infoType, Object info) {
		savedInfo.put(infoType, info);
	}

	/**
	 * Returns information about the client saved using setInfo. Based on a hash
	 * map.
	 * 回傳使用 setInfo 儲存的關於 client 的資訊。基於雜湊表。
	 * 
	 * @param infoType
	 *            identifies the type of information
	 */
	public Object getInfo(String infoType) {
		return savedInfo.get(infoType);
	}

	// RUN METHOD -------------------------------------------------------

	/**
	 * Constantly reads the client's input stream. Sends all objects that are
	 * read to the server. Not to be called.
	 * 持續讀取 client 輸入的資料流。傳送 server 讀取的所有物件。此方法不會被呼叫。
	 */
	final public void run() {
		server.clientConnected(this);

		// This loop reads the input stream and responds to messages
		// from clients
		// 此迴圈用來讀取輸入串流並回應來自 client 的訊息。
		try {
			// The message from the client 來自 client 的訊息
			Object msg;

			while (!readyToStop) {
				// This block waits until it reads a message from the client
				// and then sends it for handling by the server
				// 此區塊會一直等待直到讀到來自 client 的訊息並傳送給 server 來處理。
				msg = input.readObject();
				server.receiveMessageFromClient(msg, this);
			}
		} catch (Exception exception) {
			if (!readyToStop) {
				try {
					closeAll();
				} catch (Exception ex) {
				}

				server.clientException(this, exception);
			}
		}
	}

	// METHODS TO BE USED FROM WITHIN THE FRAMEWORK ONLY ----------------

	/**
	 * Closes all connection to the server. 關閉所有 server 的連接。
	 * 
	 * @exception IOException
	 *                if an I/O error occur when closing the connection.
	 */
	private void closeAll() throws IOException {
		try {
			// Close the socket 關閉 socket。
			if (clientSocket != null)
				clientSocket.close();

			// Close the output stream 關閉輸出資料流。
			if (output != null)
				output.close();

			// Close the input stream 關閉輸入資料流。
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

	/**
	 * This method is called by garbage collection.
	 * 此方法會被垃圾收集呼叫。
	 */
	protected void finalize() {
		try {
			closeAll();
		} catch (IOException e) {
		}
	}
}
// End of ConnectionToClient class