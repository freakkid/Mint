import info.gridworld.actor.Actor;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;
import info.gridworld.grid.Grid;

import java.awt.Color;
import java.util.ArrayList;

public class KingCrab extends CrabCritter
{
	// a kingcrab can pull other actors
    // in 3 direction in front of it 
    public void processActors(ArrayList<Actor> actors)
    {
        Location curLoc = getLocation();
    	int curDirection = getDirection();
    	Grid<Actor> grid = getGrid();
        for (Actor a : actors)
        {
         	// get empty loctions of the actor that will be pull
            ArrayList<Location> emptyLocs = grid.getEmptyAdjacentLocations(a.getLocation());
            // get the current distance between 
            // the actor and king crab
         	int curDistaceSqu = distanceSquareTwoLocation(a.getLocation(), curLoc);
            // check if the actor has other empty loction 
            // to be pull
            boolean isPulled = false;
         	for (Location loc : emptyLocs)
         	{
         		if (distanceSquareTwoLocation(loc, curLoc) > curDistaceSqu)
         		{
         			a.moveTo(loc);
                    isPulled = true;
         			break;
         		}
         	}
            // if counld not be pull
            // remove it 
            if (!isPulled) {
                a.removeSelfFromGrid();
            }
        }
    }

    // calcultate the distance between 2 loctions
    // distanceSquare = row1 * row2 + col1 * col2
    private int distanceSquareTwoLocation(Location loc1, Location loc2) 
    {   
    	return (loc1.getRow() - loc2.getRow()) * (loc1.getRow() - loc2.getRow()) +
    			(loc1.getCol() - loc2.getCol()) * (loc1.getCol() - loc2.getCol());
    }
}
