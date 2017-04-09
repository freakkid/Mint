import info.gridworld.actor.Actor;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;
import info.gridworld.grid.Grid;

import java.awt.Color;
import java.util.ArrayList;


public class ChameleonKid extends ModidfiedChameleonCritter
{

    //  a critter change its color to 
    // the color of the actor
    // in front of or behind 
    private static final double DARKENING_FACTOR = 0.05;

    public void processActors(ArrayList<Actor> actors)
    {
        int n = actors.size();
        if (n == 0) {
            setColorInProcess();
            return;
        }

        int dirs[] = {Location.AHEAD, Location.FULL_CIRCLE};
        ArrayList<Location> locs = getLocationsInDirections(dirs);

        // the actor behind and front        
        ArrayList<Actor> fbActor = new ArrayList();
        for (Actor a: actors)
        {
            // check position
            if (a.getLocation().equals(locs.get(0)) || a.getLocation().equals(locs.get(1)))
            {
                fbActor.add(a);
            }
        }
        // the actor behind and front is 2
        if (fbActor.size() == 2)
        {
            // select actor randomly
            if (Math.random() < 0.5)
            {
                setColor(fbActor.get(0).getColor());
            }
            else
            {
                setColor(fbActor.get(1).getColor());
            }
        }
        // the actor behind and front is 1
        else if (fbActor.size() == 1)
        {
            setColor(fbActor.get(0).getColor());
        }
        else {
            // act like super class
            int r = (int) (Math.random() * n);

            Actor other = actors.get(r);
            if (other != null){
                setColor(other.getColor());
            }
        }
        
    }

    public ArrayList<Location> getLocationsInDirections(int[] directions)
    {
        ArrayList<Location> locs = new ArrayList<Location>();
        Grid gr = getGrid();
        Location loc = getLocation();
    
        for (int d : directions)
        {
            Location neighborLoc = loc.getAdjacentLocation(getDirection() + d);
             if (gr.isValid(neighborLoc)) {
                locs.add(neighborLoc);
             }
        }
        return locs;
    }   
}
