import tkinter as tk
from tkinter import ttk


class MainWindow(tk.Tk):

  def __init__(self):
    super().__init__()

    self.title("Payment Tracker")
    self.geometry("1800x600")

    # Create a treeview widget and set up the columns
    self.tree = ttk.Treeview(self,
                             columns=("id", "apt", "tenant", "month", "year",
                                      "transaction", "debit", "credit", "date",
                                      "type", "notes"))

    self.tree.heading("id", text="ID")
    self.tree.heading("apt", text="Apt")
    self.tree.heading("tenant", text="Tenant")
    self.tree.heading("month", text="Month")
    self.tree.heading("year", text="Year")
    self.tree.heading("transaction", text="Transaction")
    self.tree.heading("debit", text="Debit")
    self.tree.heading("credit", text="Credit")
    self.tree.heading("date", text="Date")
    self.tree.heading("type", text="Type")
    self.tree.heading("notes", text="Notes")
    self.tree.grid(row=0, column=0, rowspan=7, sticky="nsew")

    # Create a frame to hold the search results table
    self.search_frame = tk.Frame(self)
    self.search_frame.grid(row=0, column=3, rowspan=7, sticky="nsew")
    # Hide the search results frame by default
    self.search_frame.grid_remove()

    # Create a treeview widget for the search results
    self.search_tree = ttk.Treeview(
      self.search_frame,
      columns=("id", "apt", "tenant", "month", "year", "transaction", "debit",
               "credit", "date", "type", "notes"))

    self.search_tree.heading("id", text="ID")
    self.search_tree.heading("apt", text="Apt")
    self.search_tree.heading("tenant", text="Tenant")
    self.search_tree.heading("month", text="Month")
    self.search_tree.heading("year", text="Year")
    self.search_tree.heading("transaction", text="Transaction")
    self.search_tree.heading("debit", text="Debit")
    self.search_tree.heading("credit", text="Credit")
    self.search_tree.heading("date", text="Date")
    self.search_tree.heading("type", text="Type")
    self.search_tree.heading("notes", text="Notes")

    # set width of columns to 0
    self.search_tree.column("#0", width=0, stretch=True)
    self.search_tree.column("id", width=40, stretch=True)
    self.search_tree.column("apt", width=40, stretch=True)
    self.search_tree.column("tenant", width=80, stretch=True)
    self.search_tree.column("month", width=70, stretch=True)
    self.search_tree.column("year", width=40, stretch=True)
    self.search_tree.column("transaction", width=85, stretch=True)
    self.search_tree.column("debit", width=50, stretch=True)
    self.search_tree.column("credit", width=50, stretch=True)
    self.search_tree.column("date", width=80, stretch=True)
    self.search_tree.column("type", width=40, stretch=True)
    self.search_tree.column("notes", width=65, stretch=True)

    # Create input widgets
    tk.Label(self, text="ID:").grid(row=0, column=1, sticky="w")
    tk.Label(self, text="Apt:").grid(row=1, column=1, sticky="w")
    tk.Label(self, text="Tenant:").grid(row=2, column=1, sticky="w")
    tk.Label(self, text="Month:").grid(row=3, column=1, sticky="w")
    tk.Label(self, text="Year:").grid(row=4, column=1, sticky="w")
    tk.Label(self, text="Transaction:").grid(row=5, column=1, sticky="w")
    tk.Label(self, text="Debit:").grid(row=6, column=1, sticky="w")
    tk.Label(self, text="Credit:").grid(row=7, column=1, sticky="w")
    tk.Label(self, text="Date:").grid(row=8, column=1, sticky="w")
    tk.Label(self, text="Type:").grid(row=9, column=1, sticky="w")
    tk.Label(self, text="Notes:").grid(row=10, column=1, sticky="nw")
    tk.Label(self, text="Search For:").grid(row=14, column=1, sticky="nw")
    # Create a dropdown menu for selecting the search column

    self.id_input = tk.Entry(self)
    self.apt_input = tk.Entry(self)
    self.tenant_input = tk.Entry(self)
    self.month_input = tk.Entry(self)
    self.year_input = tk.Entry(self)
    self.transaction_input = tk.Entry(self)
    self.debit_input = tk.Entry(self)
    self.credit_input = tk.Entry(self)
    self.date_input = tk.Entry(self)
    self.type_input = tk.Entry(self)
    self.notes_input = tk.Entry(self)
    self.add_button = tk.Button(self, text="Add Row", command=self.add_payment)
    self.delete_button = tk.Button(self,
                                   text="Delete Selected Row",
                                   command=self.delete_payment)
    self.save_button = tk.Button(self,
                                 text="Update Selected Row",
                                 command=self.save_payment)
    self.search_input = tk.Entry(self)
    self.column_var = tk.StringVar()
    self.column_menu = tk.OptionMenu(self, self.column_var, "id", "apt",
                                     "tenant", "month", "year", "transaction",
                                     "debit", "credit", "date", "type",
                                     "notes")

    self.search_button = tk.Button(self, text="Search", command=self.search)

    # Add the input widgets to the grid
    self.id_input.grid(row=0, column=2)
    self.apt_input.grid(row=1, column=2)
    self.tenant_input.grid(row=2, column=2)
    self.month_input.grid(row=3, column=2)
    self.year_input.grid(row=4, column=2)
    self.transaction_input.grid(row=5, column=2)
    self.debit_input.grid(row=6, column=2)
    self.credit_input.grid(row=7, column=2)
    self.date_input.grid(row=8, column=2)
    self.type_input.grid(row=9, column=2)
    self.notes_input.grid(row=10, column=2)
    self.add_button.grid(row=11, column=2, sticky="w")
    self.delete_button.grid(row=12, column=2, sticky="w")
    self.save_button.grid(row=13, column=2, sticky="w")
    self.search_input.grid(row=14, column=2)
    self.search_button.grid(row=15, column=2, sticky="w")
    self.column_var = tk.StringVar()
    self.column_menu.grid(row=15, column=1)

    # Set up the treeview to respond to double-clicks
    self.tree.bind("<Double-1>", self.on_double_click)

    # set width of columns to 0
    self.tree.column("#0", width=0, stretch=True)
    self.tree.column("id", width=40, stretch=True)
    self.tree.column("apt", width=40, stretch=True)
    self.tree.column("tenant", width=80, stretch=True)
    self.tree.column("month", width=70, stretch=True)
    self.tree.column("year", width=40, stretch=True)
    self.tree.column("transaction", width=85, stretch=True)
    self.tree.column("debit", width=50, stretch=True)
    self.tree.column("credit", width=50, stretch=True)
    self.tree.column("date", width=80, stretch=True)
    self.tree.column("type", width=40, stretch=True)
    self.tree.column("notes", width=65, stretch=True)

  def add_payment(self):
    id = self.id_input.get()
    apt = self.apt_input.get()
    tenant = self.tenant_input.get()
    month = self.month_input.get()
    year = self.year_input.get()
    transaction = self.transaction_input.get()
    debit = self.debit_input.get()
    credit = self.credit_input.get()
    date = self.date_input.get()
    type = self.type_input.get()
    notes = self.notes_input.get()

    # Insert a new item and set the values for each column
    item = self.tree.insert("",
                            "end",
                            values=(id, apt, tenant, month, year, transaction,
                                    debit, credit, date, type, notes))

  def delete_payment(self):
    """Delete a payment from the treeview."""
    selection = self.tree.selection()
    if selection:
      self.tree.delete(selection[0])

  def edit_payment(self):
    """Edit a payment in the treeview."""
    selection = self.tree.selection()
    if selection:
      item = self.tree.item(selection[0])
      self.id_input.delete(0, "end")
      self.id_input.insert(0, item["values"][0])
      self.apt_input.delete(0, "end")
      self.apt_input.insert(0, item["values"][1])
      self.tenant_input.delete(0, "end")
      self.tenant_input.insert(0, item["values"][2])
      self.month_input.delete(0, "end")
      self.month_input.insert(0, item["values"][3])
      self.year_input.delete(0, "end")
      self.year_input.insert(0, item["values"][4])
      self.transaction_input.delete(0, "end")
      self.transaction_input.insert(0, item["values"][5])
      self.debit_input.delete(0, "end")
      self.debit_input.insert(0, item["values"][6])
      self.credit_input.delete(0, "end")
      self.credit_input.insert(0, item["values"][7])
      self.date_input.delete(0, "end")
      self.date_input.insert(0, item["values"][8])
      self.type_input.delete(0, "end")
      self.type_input.insert(0, item["values"][9])
      self.notes_input.delete(0, "end")
      self.notes_input.insert(0, item["values"][10])

  def on_double_click(self, event):
    """Populate the input widgets with the selected payment's values."""
    item = self.tree.item(self.tree.focus())
    self.id_input.delete(0, "end")
    self.id_input.insert(0, item["values"][0])
    self.apt_input.delete(0, "end")
    self.apt_input.insert(0, item["values"][1])
    self.tenant_input.delete(0, "end")
    self.tenant_input.insert(0, item["values"][2])
    self.month_input.delete(0, "end")
    self.month_input.insert(0, item["values"][3])
    self.year_input.delete(0, "end")
    self.year_input.insert(0, item["values"][4])
    self.transaction_input.delete(0, "end")
    self.transaction_input.insert(0, item["values"][5])
    self.debit_input.delete(0, "end")
    self.debit_input.insert(0, item["values"][6])
    self.credit_input.delete(0, "end")
    self.credit_input.insert(0, item["values"][7])
    self.date_input.delete(0, "end")
    self.date_input.insert(0, item["values"][8])
    self.type_input.delete(0, "end")
    self.type_input.insert(0, item["values"][9])
    self.notes_input.delete(0, "end")
    self.notes_input.insert(0, item["values"][10])

  def save_payment(self):
    """Save the values in the input widgets to the selected payment in the treeview."""
    selection = self.tree.selection()
    if selection:
      self.tree.item(selection[0],
                     text=self.id_input.get(),
                     values=(self.id_input.get(), self.apt_input.get(),
                             self.tenant_input.get(), self.month_input.get(),
                             self.year_input.get(),
                             self.transaction_input.get(),
                             self.debit_input.get(), self.credit_input.get(),
                             self.date_input.get(), self.type_input.get(),
                             self.notes_input.get()))

  def search(self):
    # Retrieve the search criteria
    column = self.column_var.get()
    keyword = self.search_input.get()

    # Create a new Toplevel window
    search_window = tk.Toplevel(self)
    search_window.title("Search Results")
    search_window.geometry("800x400")

    # Create a Treeview in the new window
    search_tree = ttk.Treeview(search_window,
                               columns=("id", "apt", "tenant", "month", "year",
                                        "transaction", "debit", "credit",
                                        "date", "type", "notes"))
    # Configure the Treeview columns just like in the main window
    # [Add here the same code you used to set up the main treeview's columns and headings]

    # Call the method to populate the treeview with search results
    self.populate_search_results(search_tree, column, keyword)

    # Display the Treeview
    search_tree.pack(expand=True, fill="both")


  
  def populate_search_results(self, search_tree, column, keyword):
    # Clear existing entries in the search_tree
    search_tree.delete(*search_tree.get_children())

    # Mapping of column names to their respective index in the treeview
    column_mapping = {"id": 0, "apt": 1, "tenant": 2, "month": 3, "year": 4, 
                      "transaction": 5, "debit": 6, "credit": 7, "date": 8, 
                      "type": 9, "notes": 10}

    # Get the index of the column to search
    column_index = column_mapping.get(column)

    # Check if column is valid
    if column_index is not None:
        # Set up columns and headings in the search_tree
        search_tree['columns'] = ("id", "apt", "tenant", "month", "year", "transaction",
                                  "debit", "credit", "date", "type", "notes")
        for col in search_tree['columns']:
            search_tree.heading(col, text=col.capitalize())

        # Iterate over all items in the main treeview
        for item in self.tree.get_children():
            values = self.tree.item(item, "values")
            # Print values for debugging
            print(f"Comparing '{keyword}' in '{values[column_index]}'")
            # Check if the search keyword is in the specified column
            if keyword.lower() in str(values[column_index]).lower():
                # Insert the matching entry into the search results treeview
                search_tree.insert("", "end", values=values)


def main():
  window = MainWindow()
  window.mainloop()


if __name__ == "__main__":
  main()
