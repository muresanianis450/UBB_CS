
from datetime import date
from src.domain.domain import Rental

class ValidatorException(Exception):
    def __init__(self, message_list=None):
        self.message_list = message_list if message_list else ["Validation error!"]

    @property
    def message(self):
        return self.message_list

    def __str__(self):
        return "\n".join(self.message)  # Simplified string conversion


class RentalValidator:
    # Define the fixed "present" date as 01.01.2000
    PRESENT_DATE = date(2000, 1, 1)

    def validate(self, rental: Rental):
        if not isinstance(rental, Rental):
            raise TypeError("Not a Rental object!")

        _errorlist = []

        # Use the fixed "present" date
        now = self.PRESENT_DATE

        # Validate rental dates
        if rental.rented_date > now:
            _errorlist.append("Rental start date cannot be in the future (relative to 01.01.2000).")
        if rental.due_date and rental.due_date < rental.rented_date:
            _errorlist.append("Due date cannot be earlier than the rented date.")
        if rental.returned_date:
            if rental.returned_date < rental.rented_date:
                _errorlist.append("Returned date cannot be earlier than the rented date.")
            if rental.due_date and rental.returned_date > rental.due_date:
                _errorlist.append("Returned date cannot be after the due date.")

        # Validate rental period (minimum 5 days)
        if len(rental) < 5:
            _errorlist.append("Rental period must be at least 5 days.")

        # Raise ValidatorException if there are errors
        if _errorlist:
            raise ValidatorException(_errorlist)
