# Noun-Verb Analysis
Noun-Verb analysis is a technique used to convert plain English requirements into possible classes and methods. 

## Identified Nouns
Nouns in the requirements become candidate objects/classes:
*Cinema, Screen, Seat, Movie, Show, ShowSeat, Customer, Booking, Payment, UpiPayment, CardPayment, CashPayment, BookingService, PriceCalculator, TicketPrinter, Ticket.*

## Identified Verbs
Verbs in the requirements become possible operations/actions:
*book, select, view, calculate, pay, process, create, print, check availability.*

## Noun-Verb Examples
- *"Customer books a seat."* 
  - **Customer** → Object/Class
  - **books** → Operation/Method
  - **seat** → Object/Class
- *"PriceCalculator calculates ticket price."*
  - **PriceCalculator** → Class
  - **calculates** → Method/Operation

*Note: Noun-verb analysis is an analysis technique, not automatically a final class design. These candidates are refined before creating the UML.*
