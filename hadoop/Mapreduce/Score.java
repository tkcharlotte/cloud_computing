import java.io.IOException;  
import java.util.StringTokenizer;        
import org.apache.hadoop.conf.Configuration;  
import org.apache.hadoop.fs.Path;  
import org.apache.hadoop.io.IntWritable;  
import org.apache.hadoop.io.FloatWritable; 
import org.apache.hadoop.io.Text;  
import org.apache.hadoop.mapreduce.Job;  
import org.apache.hadoop.mapreduce.Mapper;  
import org.apache.hadoop.mapreduce.Reducer;  
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;  
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;  
import org.apache.hadoop.util.GenericOptionsParser;  
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;            
public class Score {  
          
        //嵌套类 Mapper  
        //Mapper<keyin,valuein,keyout,valueout>  
public static class FirstMapper extends Mapper<Object, Text, Text, Text>{  
        
    //private final static IntWritable one = new IntWritable(1);  
                      
     protected void map(Object key, Text value, Context context)throws IOException, InterruptedException {  
        String id = ((FileSplit) context.getInputSplit()).getPath().getName();  
         Text word = new Text(id);     
         //IntWritable score = new IntWritable();
         Text score = new Text();
         //String[] s=value.toString().split("\n"); 
         StringTokenizer itr = new StringTokenizer(value.toString(),"\n",false);  
        while(itr.hasMoreTokens())
        {
               String a=itr.nextToken();
               String[] split=a.split(" "); 
                score.set(split[2]);
              context.write(word, score);//Context机制
        }
               
                
            }  
        }         
        //嵌套类Reducer  
        //Reduce<keyin,valuein,keyout,valueout>  
        //Reducer的valuein类型要和Mapper的valueout类型一致,Reducer的valuein是Mapper的valueout经过shuffle之后的值  
public static class FirstReducer extends Reducer<Text, Text, Text, Text>{  
    
    protected void reduce(Text key, Iterable<Text> values,  Context context)  throws IOException, InterruptedException {  
               int  excellent = 0,good =0 ,common=0,normal=0,bad=0;  
               for(Text i:values){  
                   String a=i.toString();
                  int score=Integer.parseInt(a);
                    if(score>=90)
                    {
                        excellent=excellent+1;
                    }  
                    else if(score>=80&&score<90)
                    {
                        good=good+1;
                    }  
                 	   else if(score>=70&&score<80)
                    {
                        common=common+1;
                    }  
                    else if(score>=60&&score<70)
                    {
                        normal=normal+1;
                    }  
                    else if(score<60)
                    {
                        bad=bad+1;
                    }   
                }  
                String e=excellent +"";
                String g=good+"";
                String m=common+"";
                String y=normal+"";
                String n=bad+"";
                String result=" "+e+" "+g+" "+m+" "+y+" "+n;
                context.write(key,new Text(result));//Context机制  
                    }  
        }

public static class SecondMapper extends Mapper<Object, Text, Text, Text>{  
          
     private Text word = new Text("result is ");                       
     protected void map(Object key, Text value, Context context)throws IOException, InterruptedException { 
         Text score = new Text(value);
              context.write(word, score);//Context机制
        
               
                
            }  
        } 

public static class SecondReducer extends Reducer<Text, Text, Text, Text>{  
    
    protected void reduce(Text key, Iterable<Text> values,  Context context)  throws IOException, InterruptedException {  
                    int bad=0,normal=0,common=0,good=0,excellent=0;
                    for(Text i:values){

                String[] array = i.toString().split(" ");
                 excellent= excellent+ Integer.parseInt(array[1]);
                 good = good+Integer.parseInt(array[2]);
                 common = common+Integer.parseInt(array[3]);
                 normal = normal+Integer.parseInt(array[4]);
                 bad=bad+Integer.parseInt(array[5]);
                     }
                    
                 String result = excellent+""+" "+good+""+" "+common+""+" "+normal+""+" "+bad+""; 
                context.write(key,new Text(result));


                    }  
        }

          
public static void main(String[] args) throws Exception{  
            Configuration conf = new Configuration();
            Job job = new Job(conf,"Score");
            job.setJarByClass(Score.class);  
            job.setMapperClass(FirstMapper.class);  
            job.setReducerClass(FirstReducer.class);
            job.setOutputKeyClass(Text.class);  
            job.setOutputValueClass(Text.class); 
            
            Job job1 = new Job(conf,"Score1"); 
            job1.setJarByClass(Score.class);
            job1.setMapperClass(SecondMapper.class);  
            job1.setReducerClass(SecondReducer.class);   
            job1.setOutputKeyClass(Text.class);
            job1.setOutputValueClass(Text.class);  
            FileInputFormat.addInputPath(job, new Path(("/user/hadoop/input")));//传入input path  
            FileOutputFormat.setOutputPath(job, new Path("/user/hadoop/tmp")); 
            FileInputFormat.addInputPath(job1, new Path("/user/hadoop/tmp"));//传入input path  
            FileOutputFormat.setOutputPath(job1, new Path("/user/hadoop/out"));                      
            if(job.waitForCompletion(true))
           {
           System.exit(job1.waitForCompletion(true)?0:1);
            }
 
       }   
    }  
