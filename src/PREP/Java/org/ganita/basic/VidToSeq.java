package org.ganita.basic;
import java.io.IOException;
import java.net.URI;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.SequenceFile;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.BytesWritable;

public class VidToSeq {
    public static void main(String args[]) throws Exception {

        Configuration confHadoop = new Configuration();     
        confHadoop.addResource(new Path("/usr/local/hadoop/etc/hadoop/core-site.xml"));
        confHadoop.addResource(new Path("/usr/local/hadoop/etc/hadoop/hdfs-site.xml"));   
        FileSystem fs = FileSystem.get(confHadoop);
	FileStatus fstatus = new FileStatus();
        Path inPath = new Path("/user/terry/B-E-D/Kasthuri11/hdf5/x-4000/y-4000/Kasthuri11_4000_4800_4000_4800_100_200.h5");
        Path outPath = new Path("/user/terry/B-E-D/Kasthuri11/seq/hdf5/x-4000/y-4000/Kasthuri11_4000_4800_4000_4800_100_200.seq");
        FSDataInputStream in = null;
        Text key = new Text();
        BytesWritable value = new BytesWritable();
        SequenceFile.Writer writer = null;
        try{
            in = fs.open(inPath);
	    fstatus = fs.getFileStatus(inPath);
	    System.out.println("File length "+fstatus.getLen());
            byte buffer[] = new byte[(int) fstatus.getLen()];
            //byte buffer[] = new byte[in.available()];
            in.readFully(0,buffer);
            writer = SequenceFile.createWriter(fs, confHadoop, outPath, key.getClass(),value.getClass());
            writer.append(new Text(inPath.getName()), new BytesWritable(buffer));
        }catch (Exception e) {
            System.out.println("Exception MESSAGES = "+e.getMessage());
        }
        finally {
            IOUtils.closeStream(writer);
            System.out.println("Sequence file build completed!");
        }
    }
}
