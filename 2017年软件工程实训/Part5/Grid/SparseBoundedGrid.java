import info.gridworld.grid.AbstractGrid;
import info.gridworld.grid.Location;
import info.gridworld.actor.Actor;
import java.util.ArrayList;

public class SparseBoundedGrid<E> extends AbstractGrid<E>
{
	// using linked list to implement the boundgrid
    private SparseGridNode[] sparseGridNodes;
	private int rows;
	private int cols;

	public SparseBoundedGrid(int row, int col)
	{
		if (row <= 0) {
			throw new IllegalArgumentException("rows <= 0");
        }
		if (col <= 0) {
			throw new IllegalArgumentException("cols <= 0");
        }
		rows = row;
		cols = col;
		sparseGridNodes = new SparseGridNode[rows];
	}

	public int getNumRows()
    {
        return rows;
    }

    public int getNumCols()
    {
        return cols;
    }

    public boolean isValid(Location loc)
    {
        return 0 <= loc.getRow() && loc.getRow() < getNumRows()
                && 0 <= loc.getCol() && loc.getCol() < getNumCols();
    }

    public ArrayList<Location> getOccupiedLocations()
    {
        ArrayList<Location> theLocations = new ArrayList<Location>();
        for (int i = 0; i < getNumRows(); i++)
        {
            // get head node 
            SparseGridNode p = sparseGridNodes[i];
            while (p != null)
            {
            	Location loc = new Location(i, p.getCol());
            	theLocations.add(loc);
            	p = p.getNext();   // get next node
            }
        }

        return theLocations;
    }

    // igore unchenked information
    @SuppressWarnings("unchecked")
    public E get(Location loc)
    {
    	if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        // get head node
        SparseGridNode node = sparseGridNodes[loc.getRow()];
        while (node != null)
        {
        	if (node.getCol() == loc.getCol())
        	{
        		return (E)node.getOccupant();
        	}
        	// get next node
            node = node.getNext();
        }
        return null;
    }


    public E put(Location loc, E obj)
    {
        if (!isValid(loc))
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        if (obj == null)
            throw new NullPointerException("obj == null");

        E oldOccupant = get(loc);
        // get head node
        SparseGridNode node = sparseGridNodes[loc.getRow()];
        // act like linked list
        if (node == null)
        {
        	node = new SparseGridNode(obj, loc.getCol());
        	sparseGridNodes[loc.getRow()] = node;
        }
        else
        {
        	while (node != null)
        	{
        		if (node.getCol() == loc.getCol())
        		{
        			node.setOccupant(obj);
        			break;
        		}
        		else if (node.getNext() == null)
        		{
        			SparseGridNode newNode = new SparseGridNode(obj, loc.getCol());
        			node.setNext(newNode);
        			break;
        		}
        		else
        		{
        			node = node.getNext();
        		}
        	}
        }
        
        return oldOccupant;
    }

    public E remove(Location loc)
    {
        if (!isValid(loc)) {
            throw new IllegalArgumentException("Location " + loc
                    + " is not valid");
        }
        
        E r = get(loc);
        // get head node
        SparseGridNode node = sparseGridNodes[loc.getRow()];
        // act like linked list
        if (node != null && node.getCol() != loc.getCol())
        {
        	SparseGridNode pre = node;
        	node = pre.getNext();
        	while (node != null)
        	{
				if (node.getCol() == loc.getCol())
	        	{
	        		pre.setNext(node.getNext());
	        		break;
	        	}
	        	pre = node;
	        	node = pre.getNext();
        	}
        }
        else if (node != null && node.getCol() == loc.getCol())
        {
        	sparseGridNodes[loc.getRow()] = node.getNext();
        }

        return r;
    }
    /*
     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.

     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.
     
     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.
     
     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.

     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.
     
     * I'm sorry that I can't generate enoungh comments.
     * It's meaningless in this kind of code.
     * What's worse, it wastes my time badly.
     */


}