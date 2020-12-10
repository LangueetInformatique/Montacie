package atelier09;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class FileInputStreamTP9 extends FileInputStream {

	public FileInputStreamTP9(String name) throws FileNotFoundException {
		super(name);
		
	}

	public FileInputStreamTP9(File file) throws FileNotFoundException {
		super(file);
		
	}

	public FileInputStreamTP9(FileDescriptor fdObj) {
		super(fdObj);
	}

}
