/*
*  A BlusterCritter changed its color
*  Date : 2017-04-09
*  by ugnamsung
*/
import info.gridworld.actor.Actor;
import info.gridworld.actor.Rock;
import info.gridworld.actor.Critter;
import info.gridworld.grid.Location;
import info.gridworld.grid.Grid;

import java.awt.Color;
import java.util.ArrayList;

public class BlusterCritter extends Critter
{
 	private static final double DARKENING_FACTOR = 0.05;
 	// the numebr of critters 24 grids
    private int courage;

   	public BlusterCritter()
   	{
    	courage = 1;
    }
    

    public int getCourage()
    {
    	return courage;
    }

    public void setCourage(int newCourage)
    {
    	courage = newCourage;
    }

    public ArrayList<Actor> getActors()
    {
        int row = getLocation().getRow();
        int col = getLocation().getCol();
        
        ArrayList<Actor> critters = new ArrayList<Actor>();

        // get 24 grids by 2 loops
        for (int r = -2; r <= 2; r++) 
        {
        	for (int c = -2; c <= 2; c++)
        	{
        		// the location of itself
                if (r == 0 && c== 0){
        			continue;
                }

        		Location loc = new Location(row + r, col + c);
                Grid<Actor> grid = getGrid();
        		if (grid.isValid(loc))
        		{
        			Actor a = grid.get(loc);
        			if (a instanceof Critter) 
        			{
        				critters.add(a);
        			}
        		}
        	}
        }
        return critters;
    }

    public void processActors(ArrayList<Actor> actors)
    {
        // get the number of actors
        int n = actors.size();
        Color c = getColor();
        int red = (int) c.getRed();
        int green = (int) c.getGreen();
        int blue = (int) c.getBlue();
        // lighter
        if (n < courage) {
            red *= (1 + DARKENING_FACTOR);
            green *= (1 + DARKENING_FACTOR);
            blue *= (1 + DARKENING_FACTOR);
        }
        // darker
        else
        {
        	red *= (1 - DARKENING_FACTOR);
            green *= (1 - DARKENING_FACTOR);
            blue *= (1 - DARKENING_FACTOR);
        }
        //  if the color factor is overflow 
        // if not, set color
        if (isValidColor(red) && isValidColor(green) && isValidColor(blue)){
        	setColor(new Color(red, green, blue));
        }
    }

    // check if the color factor is overflow
    private boolean isValidColor(int color)
    {
    	return (0 <= color && color <= 255);
    }

}
