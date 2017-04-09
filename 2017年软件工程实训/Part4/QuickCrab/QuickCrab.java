import info.gridworld.actor.Actor;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;
import info.gridworld.grid.Grid;

import java.awt.Color;
import java.util.ArrayList;

public class QuickCrab extends CrabCritter
{
    // a quick crab can move left and right ramdonly
    // and move 2 grids
    // if there is no grids, move like a crab
    public void makeMove(Location loc)
    {
    	Location curLoc = getLocation();
    	int curDirection = getDirection();
        // get 2 left locations
		Location leftNeighborLoc = curLoc.getAdjacentLocation(curDirection + Location.LEFT);
        Location leftNextNeighborLoc = leftNeighborLoc.getAdjacentLocation(curDirection + Location.LEFT);
        // get 2 right locations
        Location rightNeighborLoc = curLoc.getAdjacentLocation(curDirection + Location.RIGHT);
        Location rightNextNeighborLoc = rightNeighborLoc.getAdjacentLocation(curDirection + Location.RIGHT);
        // initial a null
        Actor leftNeighborActor = null;
        Actor leftNextNeighborActor = null;
        Actor rightNeighborActor = null;
        Actor rightNextNeighborActor = null;

        boolean isLeftValid = false;
        boolean isRightValid = false;

        Grid<Actor> grid = getGrid();
        // if left valid
        if (grid.isValid(leftNeighborLoc) && grid.isValid(leftNextNeighborLoc))
        {
        	leftNeighborActor = grid.get(leftNeighborLoc);
        	leftNextNeighborActor = grid.get(leftNextNeighborLoc);
        	
         	if (leftNeighborActor == null && leftNextNeighborActor == null) {
        		isLeftValid = true;
            }
        }
        // if right valid
        if (grid.isValid(rightNeighborLoc) && grid.isValid(rightNextNeighborLoc))
        {
        	rightNeighborActor = grid.get(rightNeighborLoc);
         	rightNextNeighborActor = grid.get(rightNextNeighborLoc);

         	if (rightNeighborActor == null && leftNextNeighborActor == null) {
        		isRightValid = true;
            }
        }
        // if both valid
        if (isLeftValid && isRightValid)
        {
	        // move ramdonly
            if (Math.random() < 0.5)
	        {
	        	moveTo(leftNextNeighborLoc);
	            
	        }
	        else{
	        	moveTo(rightNextNeighborLoc);
	        }
        }
        // right valid only
        else if (isRightValid && !isLeftValid)
        {
        	moveTo(rightNextNeighborLoc);
        }
        // left valid only
        else if (!isRightValid && isLeftValid)
        {
        	moveTo(leftNextNeighborLoc);
        }
        else
        {
        	super.makeMove(loc);
        }
        
    }	
}
