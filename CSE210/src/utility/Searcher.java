package utility;

import entity.Tweet;
import lucene.LuceneSearcher;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.search.TopDocs;


/**
 * Used for searching both basic and full text search.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li>a Lucene searcher that enables searching the index files, as a LuceneSearcher instance; </li>
 *   </ul> 
 * @see LuceneSearcher
 * @author Sahand Sabour
 */

public class Searcher {
    private static final LuceneSearcher ls= new LuceneSearcher();
    
    /**
     * Searches for a given keyword and displays all the tweets that contain an occurrence of that keyword.
     * @param keyword the keyword that the user has entered
     * @param tweets the list of of maps between the tweets and their favorites+retweets {@code List <Map.Entry<Tweet, Integer>>}.
     * the mapping isn't really necessary but since a list of maps was made prior to creating this instance (in Sorter class),
     * the addition of an extra for loop to create a list of tweet instances was not implemented.
     */
    public static void searchKeyword(String keyword, List <Map.Entry<Tweet, Integer>> tweets){
        System.out.println("\n"+"=".repeat(100));
        System.out.println("Initiating basic search for "+ keyword);
        int matchesFound= 0;
        for (int i=0; i<tweets.size();i++){
            Tweet currentTweet= tweets.get(i).getKey();
            //searchString is the content of the tweet and is the string that would be searched, hence the name searchString
            String searchString= currentTweet.getContent();
            if (searchString.toLowerCase().contains(keyword.toLowerCase())){
                System.out.println( String.format("%1$2s", matchesFound+1)+". "+searchString+"\n");
                matchesFound++;
            }
        }
        if(matchesFound==0) System.out.println("No matches found...");
        
        System.out.println("=".repeat(100)+"\n");
    }
    
    /**
     * Searches for a given keyword/sentence and shows the top 15 results using the methods in LuceneSearcher
     * @see LuceneSearcher#search(String)
     * @see LuceneSearcher#show(TopDocs)
     * @param sentence the keyword/sentence that the user wants to search
     */
    public static void searchFullText(String sentence) {
        System.out.println("\n"+"=".repeat(100));
        System.out.println("Initiating full text search for "+ sentence);
        System.out.println("\n* Finding matching tweets *\n");
        //Check to see whether there are characters in the string that couldn't be parsed (illegal characters)
        try{
            TopDocs foundDocs= ls.search(sentence);
            ls.show(foundDocs);
        }
        catch (IOException | ParseException e){
            System.out.println("Unable to perform full text search...");
        }
        System.out.println("=".repeat(100)+"\n");
    }
    
}
