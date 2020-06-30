package entity;

/**
 * Stores data for a tweet.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li>the tweet id, as a string;</li>
 *      <li>the date that the tweet was posted, as a string;</li>
 *      <li>the hour that the tweet was posted, as a string;</li>
 *      <li>the user that posted the tweet, as an instance of the User class;</li>
 *      <li>the content of the tweet, as a string;</li>
 *      <li>the number of favorites for the tweet, as an integer;</li>
 *      <li>the number of retweets for the tweet, as an integer;</li>
 *      <li>the latitude of the location where the tweet was posted, as a String; and</li>
 *      <li>the longitude of the location where the tweet was posted, as a String;</li>
 *   </ul>
 *  Each of the above items has a getter method!
 * 
 * @author Sahand Sabour
 */

public class Tweet {
 
    private final String id;
    private final String date;
    private final String hour;
    private final User user;
    private final String content;
    private final int favs;
    private final int retweets;
    private final String latitude;
    private final String longitude;

    /**
     * Creates a new <code>Tweet</code> instance with the given parameters.
     * @param id the tweet id
     * @param date the date that the tweet was posted
     * @param hour the hour that the tweet was posted
     * @param user the user that posted the tweet
     * @param content the content of the tweet
     * @param favs the number of favorites for the tweet
     * @param retweets the number of retweets for the tweet
     * @param latitude the latitude of the location where the tweet was posted
     * @param longitude the longitude of the location where the tweet was posted
     * 
     * @see User
     */
    public Tweet (String id,
                  String date,
                  String hour,
                  User user,
                  String content,
                  int favs,
                  int retweets,
                  String latitude,
                  String longitude)
    {
        this.id= id;
        this.date= date;
        this.hour= hour;
        this.user= user;
        this.content= content;
        this.favs= favs;
        this.retweets= retweets;
        this.latitude= latitude;
        this.longitude= longitude;
    }
    
    /**
    * Returns the id of the tweet.
    *
    * @return <code>String id</code> - id of the tweet
    */
    public String getId() {
        return id;
    }
    
    /**
    * Returns the date of the tweet (when it was posted).
    *
    * @return <code>String date</code> - date of the tweet
    */
    public String getDate() {
        return date;
    }

    /**
    * Returns the hour of the tweet (when it was posted).
    *
    * @return <code>String hour</code> - hour of the tweet
    */
    public String getHour() {
        return hour;
    }
    
    /**
    * Returns the user of the tweet (who posted it).
    *
    * @return {@link User user} - user of the tweet
    */
    public User getUser() {
        return user;
    }
    
    /**
    * Returns the content of the tweet.
    *
    * @return <code>String content</code> - content of the tweet
    */
    public String getContent() {
        return content;
    }

    /**
    * Returns the number of favorites for the tweet.
    *
    * @return <code>int favs</code> - the number of favorites for the tweet
    */
    public int getFavs() {
        return favs;
    }
    
    /**
    * Returns the number of retweets for the tweet.
    *
    * @return <code>int retweets</code> - number of retweets for the tweet
    */
    public int getRetweets() {
        return retweets;
    }
    
    /**
    * Returns the latitude of the tweet (where it was posted).
    *
    * @return <code>String latitude</code> - latitude of the tweet
    */
    public String getLatitude(){
        return latitude;
    }
    
    /**
    * Returns the longitude of the tweet (where it was posted).
    *
    * @return <code>String longitude</code> - longitude of the tweet
    */
    public String getLongitude(){
        return longitude;
    }
    
    /**
    * Overrides the toString method to print a Tweet instance
    *
    * @return <code>String</code> - custom string which shows all of the above attributes for the tweet.
    */
     @Override
    public String toString(){
        return "Tweet #"+id+
                " posted on "+date+" "+hour+
                " from ("+longitude+" , "+latitude+
                ") by "+user.getUsername()+
                " with "+favs+" FAVs & "+retweets+" RTs!"+ 
                "\n==> "+content;
    }
    
    
}
