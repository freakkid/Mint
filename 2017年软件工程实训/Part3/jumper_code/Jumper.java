/* 
 * A jumper move two cells
 * @author ugnamsung
 * @datetime 2017-03-26
 */

import info.gridworld.actor.Bug;
import info.gridworld.actor.Flower;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Actor;

import info.gridworld.grid.Grid;
import info.gridworld.grid.Location;

import java.awt.Color;
/**
 * A <code>CircleBug</code> traces out a polygon like a circle of a given size. <br />
 * The implementation of this class is testable on the AP CS A and AB exams.
 */
public class Jumper extends Bug
{

    /**
     * Constructs a jump bug
     */
    public Jumper() {}
    public Jumper(Color bugColor)
    {
        setColor(bugColor);
    }

    /**
     * Jump twoo cells
     */
    public void act()
    {
	if (canJump())
            jump();
        else
            turn();
    }

    public void jump()
    {
    	Grid<Actor> gr = getGrid();
        if (gr == null)
            return;
        // current location
        Location currentLoc = getLocation();
        // the front location
        Location frontLoc = currentLoc.getAdjacentLocation(getDirection());
        if (!gr.isValid(frontLoc))
            removeSelfFromGrid();
        // next location ofter moving, that is, the front of the front loaction
        Location nextLoc = frontLoc.getAdjacentLocation(getDirection());

        // no out of the boundry
        if (gr.isValid(nextLoc))
            moveTo(nextLoc);
        else
            removeSelfFromGrid();

    }

    public boolean canJump()
    {
    	Grid<Actor> gr = getGrid();
        if (gr == null)
            return false;
        
        // current location
        Location currentLoc = getLocation();
        // the front location
        Location frontLoc = currentLoc.getAdjacentLocation(getDirection());
        if (!gr.isValid(frontLoc))
            return false;
        // next location ofter moving, that is, the front of the front loaction
        Location nextLoc = frontLoc.getAdjacentLocation(getDirection());
        if (!gr.isValid(nextLoc))
            return false;

        // nextNeighbor is null or a flower
        // jumper can move
        Actor nextNeighbor = gr.get(nextLoc);
        return (nextNeighbor == null || nextNeighbor instanceof Flower);
    }

}
