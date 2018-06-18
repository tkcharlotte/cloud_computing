import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import java.io.File;
public class Multiupload{
public static void main(String[] args) throws IOException
	{
	Configuration conf= new Configuration();
	String dir = "/home/hadoop/Desktop/file/";
	File file = new File(dir);
	String[] filelist = file.list();
	Path dstPath= new Path("/");
	FileSystem fs = FileSystem.get(conf);
	for(int i=0;i<filelist.length;i++){
	Path srcPath = new Path(dir+filelist[i]);
	fs.copyFromLocalFile(srcPath, dstPath);
			}
	fs.close();
	}
}
