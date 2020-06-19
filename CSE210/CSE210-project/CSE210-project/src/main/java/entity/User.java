package entity;

/**
 * Stores data for a user.
 * 
 *  Instances of this class store:
 *    <ul>
 *      <li>the user's username, as a string;</li>
 *      <li>the user's nickname, as a string; and</li>
 *      <li>the number of user's followers, as a string;</li>
 *   </ul>
 *  Each of the above items has a getter method!
 * 
 * @author Sahand Sabour
 */

public class User {
    
    private final String username;
    private final String nickname;
    private final int followers;

    /**
     * Creates a new <code>User</code> instance with the given parameters
     * @param username the user's username
     * @param nickname the user's nickname
     * @param followers the number of user's followers
     */
    public User(String username,
                String nickname,
                int followers)
    {
        this.username= username;
        this.nickname= nickname;
        this.followers= followers;
    }
    
    /**
    * Returns the username of the user
    *
    * @return <code>String username</code> - username of the user
    */
    public String getUsername(){
        return username;
    }

    /**
    * Returns the nickname of the user
    *
    * @return <code>String nickname</code> - nickname of the user
    */
    public String getNickname(){
        return nickname;
    }

    /**
    * Returns the number of user's followers
    *
    * @return <code>int followers</code> - number of user's followers
    */
    public int getFollowers(){
        return followers;
    }
    
    /**
    * Overrides the toString method to print a User instance
    *
    * @return <code>String</code> - custom string which shows all of the above attributes for the user.
    */
    @Override
    public String toString(){
        return username+" known as "+ nickname+ " with "+ followers+" followers!";
    }

}
