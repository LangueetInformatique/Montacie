package cours10;

import java.rmi.server.*;
import java.net.InetAddress;
import java.io.*;

public class HelloServeur extends UnicastRemoteObject implements Hello {
	final static long serialVersionUID = 1;

	private String msg;

//	 Constructeur
	public HelloServeur() throws java.rmi.RemoteException {
		try {
	this.msg = InetAddress.getLocalHost().getHostName();
		}
		catch (IOException e) {}
	}
//	 Impl�mentation de la m�thode distante.
	public String sayHello() throws java.rmi.RemoteException {
	return "Bonjour de la part de " + msg;
	}


}

