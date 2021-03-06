# Pizzeria 
## About the project
In the pizzeria on Partynicka Street there are several chefs and Mr. Piotr and Mr. Paweł - suppliers. Preparing a pizza consists of the following steps

<ul>
<li> Washing hands
<li> Activities at the counter: rolling out the dough, applying the sauce and ingredients
<li> Putting in (and taking out) the pizza from the oven (you don't have to constantly stand by the oven, if you put the pizzas there, you can do something else)
<li> Packed in a box and placed on a shelf for suppliers
</ul>

### Motivation to choose the topic
Together with my friend Patrycja, we were wondering what we like to do together. We came up with the idea that we often eat pizza together when we meet. That is why we decided that our project would be a pizzeria. It is also a very flexible in its implementation topic.
  
### Limitations:
Unfortunately, there is only 1 washbasin and a stove in the restaurant, and the size of the vegetable / cheese / sauce, etc. stand is such that only one person is comfortable working there. The oven can bake 4 pizzas at a time and the oven periodically increases the baking of pizzas currently in it. The shelf can hold a maximum of 20 boxes, otherwise the pyramid gets too high and starts falling. Suppliers can hold a maximum of 8 boxes in a thermal food bag and they do not move until it is full, so as not to go with 1 pizza.

### Threads: 
cooks, vendors, oven
### Resources: 
sink, table, stove, shelf, thermal bag
### Critical sections: 
washing hands, preparing pizza, putting it in the oven, stacking it on the shelf, packing it in a backpack

### Possible dangers:
No pizza will be made, the chefs will never wash their hands, the pizzas on the shelf will tip over, there will never be enough pizzas for a supplier to move, one supplier will still sit around doing nothing.

## Technologies
The project is made in C++ language and the animation was done using the ncurses library.

## Example linux compilation 

`g++ -o Systemy_operacyjne_2__projekt model/Cook.cpp model/Cook.h model/DeliveryMan.cpp model/DeliveryMan.h model/Oven.cpp model/Oven.h model/Shelf.cpp model/Shelf.h model/SimulationModel.cpp model/SimulationModel.h model/Sink.cpp model/Sink.h model/ThermalBag.cpp model/ThermalBag.h model/Worktop.cpp model/Worktop.h model/Controller.cpp model/Entity.cpp model/Entity.h -lncurses -lpthread`






