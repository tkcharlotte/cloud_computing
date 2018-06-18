import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
public class LocalToHDFS{
public static void main(String[] args) throws IOException
	{
	Configuration conf= new Configuration();
	Path srcPath= new Path("./333.txt");
	Path dstPath= new Path("/");
	FileSystem fs = FileSystem.get(conf);
	fs.copyFromLocalFile(srcPath, dstPath);
	fs.close();
	}
}
