import info.gridworld.actor.Actor;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;

import java.awt.Color;
import java.util.ArrayList;


public class ModidfiedChameleonCritter extends Critter
{
    private static final double DARKENING_FACTOR = 0.05;
    /**
     * Randomly selects a neighbor and changes 
     * same as that neighbor's. If there are no
     */
    public void processActors(ArrayList<Actor> actors)
    {
        int n = actors.size();
        if (n == 0) {
            setColorInProcess();
            return;
        }
        int r = (int) (Math.random() * n);

        Actor other = actors.get(r);
        setColor(other.getColor());
    }

    public void setColorInProcess()
    {
        Color c = getColor();
        // darken
        int red = (int) (c.getRed() * (1 - DARKENING_FACTOR));
        int green = (int) (c.getGreen() * (1 - DARKENING_FACTOR));
        int blue = (int) (c.getBlue() * (1 - DARKENING_FACTOR));
        // setcolor
        setColor(new Color(red, green, blue));
    }

    /**
     * Turns towards the new location as it moves.
     */
    public void makeMove(Location loc)
    {
        setDirection(getLocation().getDirectionToward(loc));
        super.makeMove(loc);
    }

}
