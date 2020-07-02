package edu.xjtlu.cse313;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.TreeMap;

import org.apache.commons.io.FileUtils;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.io.WritableComparator;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class Assignment2 extends Configured implements Tool {
   public static void main(String[] args) throws Exception {
	  // Run the jobs
      int res = ToolRunner.run(new Configuration(), new Assignment2(), args);
      // Delete the temp directory (contains un-sorted list of all bigrams)
      FileUtils.deleteDirectory(new File(args[1]+"/temp"));
      System.exit(res);
   }

   @Override
   public int run(String[] args) throws Exception {
	   // Find a list of all bigrams with number of occurances
      int job1 = findBigramsJob(args);
      // Sort the above list and find top 10 bigrams
      int job2 = sortBigramsJob(args);
      // Find a list of all lines that contain the word 'torture'
      int job3 = findTortureJob(args);
      
      int result = job1+job2+job3;
      return result;
   }
   
   public int findBigramsJob(String[] args) throws Exception {
	      //Create a new job for finding a list of all bigrams with number of occurrences
	   	  Job job = new Job(getConf(), "findingBigrams");
	      job.setJarByClass(Assignment2.class);
	      job.setOutputKeyClass(Text.class);
	      job.setOutputValueClass(IntWritable.class);
	      job.setMapperClass(Task1Mapper.class);
	      job.setReducerClass(Task1Reducer.class);
	      job.setInputFormatClass(TextInputFormat.class);
	      job.setOutputFormatClass(TextOutputFormat.class);
	      FileInputFormat.addInputPath(job, new Path(args[0]));
	      FileOutputFormat.setOutputPath(job, new Path(args[1]+"/temp"));
	      
	      //Wait until the job is finished
	      job.waitForCompletion(true);
	      
	      return 0;
	 }
   
   public int sortBigramsJob(String[] args) throws Exception {
	   //Create a new job for sorting the list of all bigrams and outputing the top 10
	      Job job = new Job(getConf(), "sortingBigrams");
	      job.setJarByClass(Assignment2.class);
	      job.setOutputKeyClass(IntWritable.class);
	      job.setOutputValueClass(Text.class);

	      job.setMapperClass(Task1SortMapper.class);
	      job.setSortComparatorClass(Task1SortComparator.class);

	      job.setInputFormatClass(TextInputFormat.class);
	      job.setOutputFormatClass(TextOutputFormat.class);

	      FileInputFormat.addInputPath(job, new Path(args[1]+"/temp"));
	      FileOutputFormat.setOutputPath(job, new Path(args[1]+"/task1"));

	      //Wait until the job is finished
	      job.waitForCompletion(true);
	      
	      return 0;
	 }
   
   public int findTortureJob(String[] args) throws Exception {
	      // Create a new job for finding all the lines that contain the word 'torture'
	      Job job = new Job();
	      job.setJarByClass(Assignment2.class);
	      job.setOutputKeyClass(IntWritable.class);
	      job.setOutputValueClass(Text.class);

	      job.setMapperClass(Task2Mapper.class);
	      
	      job.setInputFormatClass(TextInputFormat.class);
	      job.setOutputFormatClass(TextOutputFormat.class);

	      FileInputFormat.addInputPath(job, new Path(args[0]));
	      FileOutputFormat.setOutputPath(job, new Path(args[1]+"/task2"));
	      
	      //Wait until the job is finished
	      job.waitForCompletion(true);
	      
	      return 0;
	 }

   
   public static class Task1Mapper extends Mapper<LongWritable, Text, Text, IntWritable> {
      // The default value for the occurrence of each bigram
	  private final static IntWritable ONE = new IntWritable(1);
      //A text variable to temporarily store each bigram from the book
      private Text bigram = new Text();

      @Override
      public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
    	  // Removing the punctuation and extra spaces
    	  String bookContent = value.toString().toLowerCase().replaceAll("[,.;?!\'\":+]", "").replaceAll("-", " ").trim();
    	  // Getting an array of all the words in the line
    	  String [] bookLine = bookContent.split("\\s+");
    	  for (int i=0; i<bookLine.length-1; i++) {
    		  String fWord = bookLine[i];
    		  String sWord = bookLine[i+1];
    		  String bigramStr = fWord+" "+sWord;
    		  bigram.set(bigramStr);
    		  context.write(bigram, ONE);
    	  }
 
      }
   }
   
   public static class Task1SortMapper extends Mapper<LongWritable, Text, IntWritable, Text> {
	   	  // A treemap to store the top 10 bigrams
	      private TreeMap<Integer, String> top10Bigrams = new TreeMap<Integer, String>();
	      //A text variable to temporarily store each bigram from the book
	      private Text bigram = new Text();
	      
	      // Override the setup method to intialize the treemap for top 10 biagrams
	      @Override
	      public void setup(Context context)  throws IOException, InterruptedException {
	    	  top10Bigrams = new TreeMap<Integer, String>();
	      }

	      @Override
	      public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

	    	  String resultContent = value.toString();
	    	  String [] bigramValuePair = resultContent.split("\\s+");
	    	  String bigramText = bigramValuePair[0]+" "+bigramValuePair[1];
	    	  String count = bigramValuePair[2];
	    	  top10Bigrams.put(Integer.parseInt(count), bigramText);
	    	  
	    	  // Remove the first pair if more than 10 pairs are added
	    	  if (top10Bigrams.size()>10) {
	    		  top10Bigrams.remove(top10Bigrams.firstKey());
	    	  }
	    	  
	      }
	      
	      // This method would only run once, when the mapping is finished
	      // Hence, we should write to context here
	      @Override 
	      public void cleanup(Context context)  throws IOException, InterruptedException {
	    	  for (Map.Entry<Integer, String> bigramCountPair: top10Bigrams.entrySet()) {
	    		  int count = bigramCountPair.getKey();
	    		  String bigramValue = bigramCountPair.getValue();
	    		  bigram.set(bigramValue);
	    		  context.write(new IntWritable(count), bigram);
	    	  }
	      }

	   }
   
   public static class Task2Mapper extends Mapper<LongWritable, Text, IntWritable, Text> {
	   	  private int sentenceCount = 1;
	      //A text variable to temporarily store each sentence from the book that contains torture
	      private Text sentence = new Text();
	      @Override
	      public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

	    	  String bookSentence = value.toString();
	    	  // Only process the lines that contain the word 'torture' 
	    	  if (bookSentence.contains("torture")) {
	    		  sentence.set(bookSentence);
	    		  context.write(new IntWritable(sentenceCount), sentence);
	    		  sentenceCount++;
	    	  }
	 
	      }
	   }

   public static class Task1Reducer extends Reducer<Text, IntWritable, Text, IntWritable> {
	   // Find the number of occurrences for each bigram by summing the value of all the pairs with the same key
      @Override
      public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
         int sum = 0;
         for (IntWritable value : values) {
            sum += value.get();
         }
         context.write(key, new IntWritable(sum));
      }
   }
   
   public static class Task1SortComparator extends WritableComparator {
	   	  public Task1SortComparator() {
	   		  super(FloatWritable.class, true);
	   	  }
	   	  
	   	  // Override the compare method to sort the bigrams in descending order
	   	  // The key here would be number of occurrences and value would be the bigram
	   	  @SuppressWarnings("rawtypes")
	      @Override
	      public int compare(WritableComparable wc1, WritableComparable wc2) {
	    	  FloatWritable key1 = (FloatWritable) wc1;
	    	  FloatWritable key2 = (FloatWritable) wc2;
	    	  return -1 * key1.compareTo(key2);
	      }
   }
   
   
}
