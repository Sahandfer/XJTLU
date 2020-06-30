package lucene;

import java.io.IOException;
import java.nio.file.Paths;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

/**
 * Searches the documents for a keyword and shows the top 15 results.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li>the path to save the created index files, as a string; </li>
 *      <li>the directory where the index files are stored, as a Directory instance; </li>
 *      <li>an index reader which enables reading the index files, as a IndexWriter instance; and</li>
 *      <li>an index searcher which enables searching the content of the index files, as a IndexSearcher instance;</li>
 *   </ul> 
 * @author Sahand Sabour
 */

public class LuceneSearcher {
    private static final String indexPath = System.getProperty("user.dir")+"/luceneIndexes";
    private static Directory dir;
    private static IndexReader indexReader;
    private static IndexSearcher indexSearcher;
    
    /**
     * Create a <code>LuceneSearcher</code> instance.
     */
    public LuceneSearcher () {
        //Check whether the index files exists in the given path and consequently, make an index searcher
        try{
            dir= FSDirectory.open(Paths.get(indexPath));
            indexReader= DirectoryReader.open(dir);
            indexSearcher= new IndexSearcher(indexReader);
        }
        catch (IOException e){
            System.out.println("Unable to create a LuceneSearcher...");
        }
    }
    
    public TopDocs search (String sentence) throws ParseException, IOException{
        QueryParser qp = new QueryParser("content", new StandardAnalyzer());
        //Parse the user's input so that it could be used to search the index
        Query query = qp.parse(sentence);
        //Find the top 15 hits 
        TopDocs foundDocs = indexSearcher.search(query, 15);
        return foundDocs;
    }
    
    public void show(TopDocs foundDocs) throws IOException{
        int matchesFound= 1;
        if(foundDocs.totalHits.value==0) System.out.println("No matches found!\n");
        else{
            // print the found matches
            for (ScoreDoc sd : foundDocs.scoreDocs) {
                Document doc = indexSearcher.doc(sd.doc);
                System.out.println(Integer.toString(matchesFound)+". "+String.format(doc.get("content"))+"\n");
                matchesFound++;
            }
        }
        
 
    }
}
