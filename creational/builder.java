/**
 *  Builder
 *    Separate the construction of a complex object from its representation
 *      so that the same construction process can create different representations.
 *    Important to note the waiter doesn't need to know about the pizza recipes.
 *    Composition of objects can differ within the same subclass. Not shown here.
 *      This example seems more of an abstract factory example.
 *    A better builder example might be a car. Brand->Model->Trim->Options
 *    Director: the waiter;
 *    Client: the customer who chooses the type of pizza.
 **/

/* "Product" */
class Pizza {
  private String dough = "";
  private String sauce = "";
  private String topping = "";

  public void setDough(String dough) { this.dough = dough; }
  public void setSauce(String sauce) { this.sauce = sauce; }
  public void setTopping(String topping) { this.topping = topping; }

  public String getDough() { return dough; }
  public String getSauce() { return sauce; }
  public String getTopping() { return topping; }
}

/* "Abstract Builder" */
Abstract class PizzaBuilder {
  protected Pizza pizza;

  public Pizza getPizza() { return pizza; }
  public void createNewPizzaProduct() { pizza = new Pizza(); }

  public abstract void buildDough();
  public abstract void buildSauce();
  public abstract void buildTopping();
}

/* "ConcreteBuilder" */
class HawaiianPizzaBuilder extends PizzaBuilder {
  public void buidlDough() { pizza.setDough("cross"); }
  public void buildSauce() { pizza.setSauce("mild"); }
  public void buildTopping() { pizza.setTopping("ham+pineapple"); }
}

/* "ConcreteBuilder" */
class SpicyPizzaBuilder extends PizzaBuilder {
  public void buildDough() { pizza.setDough("pan baked"); }
  public void buildSauce() { pizza.setSauce("hot"); }
  public void buildTopping() { pizza.setTopping("pepperoni+salami"); }
}

/* "Director" */
class Waiter {
  private PizzaBuilder pizzaBuilder;

  public void setPizzaBuilder(PizzaBuilder pb) { pizzaBuilder = pb; }
  public Pizza getPizza() { return pizzaBuilder.getPizza(); }

  public void constructPizza() {
    pizzaBuilder.createNewPizzaProduct();
    pizzaBuilder.buildDough();
    pizzaBuilder.buildSauce();
    pizzaBuilder.buildTopping();
  }
}

/* A customer ordering a pizza */
class BuilderExample {
  public static void main(String[] args) {
    Waiter waiter = new Waiter();
    PizzaBuilder hawaiian_pizzabuilder = new HawaiianPizzaBuilder();
    PizzaBuilder spicy_pizzabuilder = new SpicyPizzaBuilder();

    waiter.setPizzaBuilder(hawaiian_pizzabuilder);
    waiter.constructPizza();

    Pizza pizza = waiter.getPizza();
  }
}
