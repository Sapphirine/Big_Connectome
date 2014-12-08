package org.ganita.basic;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Extended Iowa State utility for processing uncompressed grayscale 
 * images in Java. 
 */
public class JImEdge
{
  // We'll use a constant maximum greyscale value
  private static final int MAXVAL = 255;
    private static final int NUM_IMS = 10;
    private static int num_ims = 10;
    private static final int MAX_IMS = 1000;
    private static final int WD = 600;
    private static final int HT = 800;
    private static int[][][] ims = new int[NUM_IMS][HT][WD];
    private static int start = 0;
    private static int gradSize = 2;
  private static ArrayList<String> myIms = new ArrayList<String>();
  
  /**
   * Usage example.
   */
  public static void main(String[] args) throws FileNotFoundException
  {
      JImEdge jimEdge = new JImEdge();
    int[][] test = jimEdge.createDiagonalLine(100, 200);
    jimEdge.createFile(test, "test.pgm");
    File myFile = new File("list.txt");
    jimEdge.run(myFile);
  }

    // run main function 
    public int run(File fin)
    {
	try {
	    readFile(fin);
	    readList();
	} catch (IOException e) {
	    System.out.println(e.getMessage());
	}

	return(1);
    }
  
  /**
   * Creates an image of the given width and height 
   * containing a diagonal line.
   * @param width
   * @param height
   * @return
   */
  public static int[][] createDiagonalLine(int width, int height)
  {
    int[][] image = new int[height][width];
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        int value;
        if (i == j)
        {
          value = 0;
        }
        else
        {
          value = MAXVAL;
        }
        image[i][j] = value;
      }
    }
    return image;
  }

  /**
   * Creates an image of the given width and height 
   * containing an arc of a circle.
   * @param width
   * @param height
   * @return
   */
  public static int[][] createArc(int width, int height)
  {
    int[][] image = new int[height][width];
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        int value;
        double radius = Math.sqrt(i * i + j * j);
        if (radius < width && radius > width - 4)
        {
          value = 0;
        }
        else
        {
          value = MAXVAL;
        }
        image[i][j] = value;
      }
    }
    return image;
  }

  /**
   * Produces a negative of the given image.
   * @param image
   * @return
   */
  public static int[][] invert(int[][] image)
  {
    int width = image[0].length;
    int height = image.length;
    int[][] result = new int[height][width];
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        result[i][j] = MAXVAL - image[i][j];
      }
    }
    return result;
  }
  
  /**
   * Creates a PGM file from the given image.
   * @param image
   *   the image
   * @param filename
   *   name of the file to be created
   * @throws FileNotFoundException
   */
  public static void createFile(int[][] image, String filename) throws FileNotFoundException
  {
    PrintWriter pw = new PrintWriter(filename);
    int width = image[0].length;
    int height = image.length;
    
    // magic number, width, height, and maxval
    pw.println("P2");
    pw.println(width + " " + height);
    pw.println(MAXVAL);
    
    // print out the data, limiting the line lengths to 70 characters
    int lineLength = 0;
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        int value = image[i][j];
        
        // if we are going over 70 characters on a line,
        // start a new line
        String stringValue = "" + value;
        int currentLength = stringValue.length() + 1;
        if (currentLength + lineLength > 70)
        {
          pw.println();
          lineLength = 0;
        }
        lineLength += currentLength;
        pw.print(value + " ");
      }
    }
    pw.close();  
  }
  
  /**
   * Reads a PGM file and returns the image. The maximum greyscale
   * value is rescaled to be between 0 and 255.
   * @param filename
   * @return
   * @throws FileNotFoundException
   */
  public static int[][] readPGMFile(String filename) throws FileNotFoundException
  {
    Scanner scanner = new Scanner(new File(filename));
    scanner.next(); // magic number
    int width = scanner.nextInt();
    int height = scanner.nextInt();
    int max = scanner.nextInt();
        
    int[][] image = new int[height][width];

    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        // normalize to 255
        int value = scanner.nextInt();
        value = (int) Math.round( ((double) value) / max * MAXVAL);
        image[i][j] = value;
      }
    }
    return image;
  }
  
  /**
   * Reads a PGM file and returns the image. The maximum greyscale
   * value is rescaled to be between 0 and 255.
   * @param filename
   * @return
   * @throws FileNotFoundException
   */
    public int readPGMFile(String filename, int id) throws FileNotFoundException
  {
    Scanner scanner = new Scanner(new File(filename));
    scanner.next(); // magic number
    int width = scanner.nextInt();
    int height = scanner.nextInt();
    int max = scanner.nextInt();

    if((width != WD) || (height != HT)){
	return -1;
    }
        
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        // normalize to 255
        int value = scanner.nextInt();
        value = (int) Math.round( ((double) value) / max * MAXVAL);
        ims[id][i][j] = value;
      }
    }
    return id;
  }
    
    public int readList() throws FileNotFoundException
    {
	if(myIms.size() < num_ims){
	    num_ims = myIms.size();
	}
	for(int ii = 0; ii < num_ims; ii++){
	    readPGMFile(myIms.get(ii).toString(), ii);
	}
	return 1;
    }
  
  public static int[][] readPGMFileAlt(String filename) throws FileNotFoundException
  {
    Scanner scanner = new Scanner(new File(filename));
    scanner.next(); // skip the magic number
    int width = scanner.nextInt();
    int height = scanner.nextInt();
    int max = scanner.nextInt();
    
    int[][] image = new int[height][width];
    
    int row = 0;
    int col = 0;
    while(scanner.hasNextInt())
    {
      int value = scanner.nextInt();
      
      // re-scale the value to be between 0 and 255
      value = (int) Math.round( ((double) value) / max * MAXVAL);
      
      image[row][col] = value;
      col += 1;
      if (col == width)
      {
        col = 0;
        row += 1;
      }
    }
    return image;
  }

  public static void readFile(File fin) throws IOException {
	// Construct BufferedReader from FileReader
	BufferedReader br = new BufferedReader(new FileReader(fin));
 
	String line = null;
	while ((line = br.readLine()) != null) {
	    myIms.add(line);
		System.out.println(line);
	}
 
	br.close();
  }

    // computes 3D gradient
    public int computeGradMag() {
	
	for (int i = 0; i < HT; ++i)
	    {
		for (int j = 0; j < WD; ++j)
		    {
		    }
	    }
	
	return 1;
    }
}

