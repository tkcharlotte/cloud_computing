import java.io.IOException; 
import org.apache.hadoop.conf.Configuration; 
import org.apache.hadoop.fs.FSDataOutputStream; 
import org.apache.hadoop.fs.FileStatus; 
import org.apache.hadoop.fs.FileSystem; 
import org.apache.hadoop.fs.Path;

public class Write { 
  public static void main(String[] args) throws IOException 
  { 
   Configuration conf = new Configuration(); 
   Path inFile = new Path("/file7.txt"); 
   FileSystem hdfs = FileSystem.get(conf); 
   FSDataOutputStream os = hdfs.create(inFile); 
   os.writeUTF("test\n"); 
   os.flush(); 
   os.close(); 
  } 
}

