package lucene;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import entity.Tweet;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.FSDirectory;

/**
 * Indexes the data from the Excel file and creates the required documents.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li>the path to save the created index files, as a string;</li>
 *      <li>the directory where the index files should be stored, as a FSDirectory instance; </li>
 *      <li>a configuration setup for creating an index writer, as a IndexWriterConfig instance;</li>
 *      <li>an index writer which enable writing index files, as a IndexWriter instance; and</li>
 *      <li>the list of documents that were indexed, as a list of Document instances;</li>
 *   </ul> 
 * 
 * @author Sahand Sabour
 */


public class LuceneIndexer {
    private static final String indexPath = System.getProperty("user.dir")+"/luceneIndexes";
    private static FSDirectory dir;
    private static IndexWriterConfig config;
    private static IndexWriter indexWriter;
    private static final List<Document> documents = new ArrayList<>();
    
    /**
     * Creates a new <code>LuceneIndexer</code> instance with the given parameters.
     * This is useful for indexing the tweet's content and creating indexed documents.
     * @param tweets the list of of maps between the tweets and their favorites+retweets ({@code List <Map.Entry<Tweet, Integer>>}).
     * the mapping isn't really necessary but since a list of maps was made prior to creating this instance (in Sorter class),
     * the addition of an extra for loop to create a list of tweet instances was not implemented.
     */
    public LuceneIndexer( List <Map.Entry<Tweet, Integer>> tweets) {
        try{
           IndexWriter iw = createWriter();
           System.out.println("\nCreating the required index files...");
           // create a document for each tweet in the list and add it to the documents list
           for (int i=0; i<tweets.size();i++){
               Document doc= createDoc(tweets.get(i).getKey());
               documents.add(doc);
           }
           //delete all the documents in the index, in case previous versions exists
           iw.deleteAll();
           
           //add all the documents to the index
           iw.addDocuments(documents);
           iw.commit();
           iw.close(); 
           System.out.println("The required index files were created Successfully!");
        }
        
        catch (IOException e){
            System.out.println("Unable to create a LucenIndexer...");
        }
    }
    
    /**
     * creates an indexed document for a given Tweet instance.
     * @param tweet the given Tweet instance
     * @return <code>doc</code> - the indexed document of the Tweet instance
     */
    private static Document createDoc(Tweet tweet){
        Document doc = new Document();
        //the document only needs one field, the content of the tweet
        doc.add(new TextField("content", tweet.getContent(), Field.Store.YES));
        return doc;
    }
    
    /**
     * Creates an IndexWriter instance which is used for writing indexed documents
     * @return <code>indexWriter</code> - an instance of IndexWriter class
     * @throws IOException - when the input indexPath is not an available directory
     */
    private static IndexWriter createWriter() throws IOException {
        dir = FSDirectory.open(Paths.get(indexPath));
        config = new IndexWriterConfig(new StandardAnalyzer());
        indexWriter = new IndexWriter(dir, config);
        return indexWriter;
    }    

}


