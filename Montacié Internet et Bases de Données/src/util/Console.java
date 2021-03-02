package util;

import java.util.StringTokenizer;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.text.*;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class Console implements DocumentListener {
	private JTextArea jl;
	private Document dl;
	private RendezVous rdv;
	private boolean lect;

	public Console() {
		JFrame fen = new JFrame("Console");
		fen.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fen.setSize(640, 480);
		jl = new JTextArea();
		dl = jl.getDocument();
		dl.addDocumentListener(this);
		fen.getContentPane().add(jl);
		fen.setVisible(true);
		rdv = new RendezVous();
		lect = false;
	}

	// méthodes d'écriture
	
	public void print(String v) {
		jl.append(v);
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(char v) {
		jl.append(Character.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(boolean v) {
		jl.append(Boolean.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(byte v) {
		jl.append(Byte.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(short v) {
		jl.append(Short.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(int v) {
		jl.append(Integer.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(long v) {
		jl.append(Long.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(float v) {
		jl.append(Float.toString(v));
		jl.setCaretPosition(dl.getLength());
	}
	
	public void print(double v) {
		jl.append(Double.toString(v));
		jl.setCaretPosition(dl.getLength());
	}

	public void println(String v) {
		jl.append(v);
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(char v) {
		jl.append(Character.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(boolean v) {
		jl.append(Boolean.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(byte v) {
		jl.append(Byte.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(short v) {
		jl.append(Short.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(int v) {
		jl.append(Integer.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(long v) {
		jl.append(Long.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(float v) {
		jl.append(Float.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	
	public void println(double v) {
		jl.append(Double.toString(v));
		jl.append("\n");
		jl.setCaretPosition(dl.getLength());
	}
	// méthodes de lecture 
	private String[] lire(String mess) {
		print(mess);
		int d = dl.getLength();
		lect = true;
		rdv.attendre();
		lect = false;
		String s = null;
		try {
			s = dl.getText(d, dl.getLength() - d - 1);
		} catch (BadLocationException e) {
			e.printStackTrace();
		}

		StringTokenizer st = new StringTokenizer(s);
		String[] mots = new String[st.countTokens()];
		int i = 0;
		while (st.hasMoreTokens() == true)
			mots[i++] = st.nextToken();

		return (mots);
	}

	public boolean getBoolean(String mess) {
		String mots[] = lire(mess);
		return (Boolean.valueOf(mots[0]).booleanValue());
	}

	public char getChar(String mess) {
		String mots[] = lire(mess);
		return (mots[0].charAt(0));
	}

	public int getInt(String mess) {
		String mots[] = lire(mess);
		return (Integer.parseInt(mots[0]));
	}

	public String getString(String mess) {
		String mots[] = lire(mess);
		return (mots[0]);
	}

	public float getFloat(String mess) {
		String mots[] = lire(mess);
		return (Float.parseFloat(mots[0]));
	}

	public double getDouble(String mess) {
		String mots[] = lire(mess);
		return (Double.parseDouble(mots[0]));
	}

	// méthodes d'écoute
	public void insertUpdate(DocumentEvent arg0) {
		if (lect == true) {
			String s = null;
			try {
				s = dl.getText(dl.getLength() - 1, 1);
			} catch (BadLocationException e) {
				e.printStackTrace();
			}
			if (s.compareTo("\n") == 0) {
				rdv.partir();
			}
		}
	}

	public void removeUpdate(DocumentEvent arg0) {
	}

	public void changedUpdate(DocumentEvent arg0) {
	}

}

class RendezVous {
	public synchronized void attendre    () { 
		try {wait();}
		catch (InterruptedException e) { e.printStackTrace(); }
	}
	
	public synchronized void partir() {
		notifyAll();
	}
}
