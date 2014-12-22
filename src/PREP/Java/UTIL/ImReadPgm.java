class ImReadPgm {
    public static void main(String[] args) {
	
	// Discard the magic number
	scan.nextLine();
	// Discard the comment line
	scan.nextLine();
	// Read pic width, height and max value
	int picWidth = scan.nextInt();
	int picHeight = scan.nextInt();
	int maxvalue = scan.nextInt();
	
	fileInputStream.close();
	
	// Now parse the file as binary data
	fileInputStream = new FileInputStream(filePath);
	DataInputStream dis = new DataInputStream(fileInputStream);
	
	// look for 4 lines (i.e.: the header) and discard them
	int numnewlines = 4;
	while (numnewlines > 0) {
	    char c;
	    do {
		c = (char)(dis.readUnsignedByte());
	    } while (c != '\n');
	    numnewlines--;
	}
	
	// read the image data
	int[][] data2D = new int[picHeight][picWidth];
	for (int row = 0; row < picHeight; row++) {
	    for (int col = 0; col < picWidth; col++) {
		data2D[row][col] = dis.readUnsignedByte();
		System.out.print(data2D[row][col] + " ");
	    }
	    System.out.println();
	}
	
