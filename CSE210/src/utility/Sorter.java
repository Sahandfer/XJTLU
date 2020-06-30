package utility;

import entity.User;
import entity.Tweet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

/**
 * makes a list of {@code Map.Entry<Object, Integer>>}maps to store users and tweets
 * It also sorts and prints the top tweets and users. 
 *    <ul>
 *      <li>the list of users, as a list of {@code <User, Integer>} maps; and</li>
 *      <li>the list of tweets, as a list of {@code <Tweet, Integer>} maps; </li>
 *   </ul>
 *   Each of the above items has a get method!
 * 
 * @author Sahand Sabour
 */

public class Sorter {
    private static final List <Map.Entry<User, Integer>> users= new ArrayList<>();
    private static final List <Map.Entry<Tweet, Integer>> tweets= new  ArrayList <>();

    /**
     * Creates a <code>Sorter</code> instance with the given parameter.
     * @param data the list of rows, which is read from the Excel file (.xlsx file) 
     */
    public Sorter (List<String[]> data){
        for (int i=1; i<data.size();i++){
            String[] cellValues= data.get(i);
            
            //Initialize the parameters that are required for making a Tweet instance
            String id= cellValues[0].trim();
            String date= cellValues[1].trim();
            String hour= cellValues[2].trim();
            String username = cellValues[3].trim();
            String nickname= cellValues[4].trim();
            String content= cellValues[5].trim();
            int favs= Integer.parseInt(cellValues[6].trim());
            int retweets= Integer.parseInt(cellValues[7].trim());
            String latitude = cellValues[8].trim();
            String longitude= cellValues[9].trim();
            int followers =0;
            
            //Check if the follower's field is empty or is not int
            try{
                followers= Integer.parseInt(cellValues[10].trim());
            }
            catch (NumberFormatException| IndexOutOfBoundsException e){}
            
            User currentUser= new User(nickname, username, followers);
            Tweet currentTweet= new Tweet(id, date, hour, currentUser, content, favs, retweets, latitude, longitude);
            
            this.addUser(currentUser);
            this.addTweet(currentTweet);
            
        }
    }
    
    /**
    * Adds a User instance to the list of users
    *
    * @param user an instance of User to be added to the list of users
    */
    private void addUser(User user){
        users.add(Map.entry(user, user.getFollowers()));
    }
    
    /**
    * Adds a Tweet instance to the list of tweets
    *
    * @param tweet an instance of Tweet to be added to the list of tweets
    */
    private void addTweet(Tweet tweet){
        tweets.add(Map.entry(tweet, tweet.getFavs()+tweet.getRetweets()));
    }
    
    /**
    * Sorts the list of users from most followers to the least.
    */
    private void sortUsers(){
        //Using lambda function to sort the list of users
        Collections.sort(users, (Map.Entry<User, Integer> user1, Map.Entry<User, Integer> user2) -> user2.getValue()-user1.getValue());
    }
    
    /**
    * Sorts the list of tweets from most favorites+retweets to the least.
    */
    private void sortTweets(){
        //Using lambda function to sort the list of tweets
        Collections.sort(tweets, (Map.Entry<Tweet, Integer> tweet1, Map.Entry<Tweet, Integer> tweet2) -> tweet2.getValue()-tweet1.getValue());
    }
    
    /**
    * Prints the top ten unique users (Duplicate user is not printed).
    */
    public void printTopUsers(){
        System.out.println("\n"+"=".repeat(100));
        this.sortUsers();
        System.out.println("*< The Top 10 users are >*\n");
        
        //A list of usernames (top 10 users) that is used for printing
        ArrayList<String> topUsersList= new ArrayList<>();
        
        for (int i=0; i<users.size(); i++){
            // In case top 10 users have already been printed
            if (topUsersList.size()==10) break;
            String username= users.get(i).getKey().getUsername();
            //Check if the username has already been printed
            if (!topUsersList.contains(username)){
                topUsersList.add(username);
                System.out.println( String.format("%1$2s", topUsersList.size())+". "+users.get(i).getKey().toString());
            }
        }

        System.out.println("=".repeat(100)+"\n");
    }
    
    /**
    * Prints the top ten tweets.
    */
    public void printTopTweets(){
        System.out.println("\n"+"=".repeat(100));
        this.sortTweets();
        System.out.println("\n*< The Top 10 tweets are >*\n");
        for (int i=0; i<10;i++){
            System.out.println( String.format("%1$2s", i+1)+". "+tweets.get(i).getKey().toString()+"\n");
        }
        System.out.println("=".repeat(100)+"\n");
    }
    
    /**
    * Returns a list of maps between User instances and their followers ({@code List <Map.Entry<User, Integer>>}).
    * @return <code>users</code> - list of maps between user and their followers
    */
    public List <Map.Entry<User, Integer>> getUsers(){
        return users;
    }
    
    /**
    * Returns a list of maps between Tweet instances and their favorites+retweets ({@code List <Map.Entry<Tweet, Integer>>}).
    * @return <code>tweets</code> - list of maps between tweet and its favorites+retweets
    */
    public List <Map.Entry<Tweet, Integer>> getTweets(){
        return tweets;
    }
}
