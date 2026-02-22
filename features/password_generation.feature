Feature: Password Generation
  As a user of MeowPassword
  I want to generate secure passwords from cat names
  So that I have memorable yet secure passwords

  Scenario: Generate a default password
    When I run meowpass without arguments
    Then the exit code should be 0
    And the output should contain "Meow Password"
    And the output should contain "MOST SECURE PASSWORD MEOW SELECTED"
    And the output should show 5 candidates

  Scenario: Generated passwords contain required character types
    When I run meowpass without arguments
    Then the exit code should be 0
    And each candidate password should contain letters
    And each candidate password should contain digits
    And each candidate password should contain symbols

  Scenario: Generated passwords respect default max length
    When I run meowpass without arguments
    Then the exit code should be 0
    And the selected password should be at most 25 characters long

  Scenario: Generate password with custom number count
    When I run meowpass with "--numbers 5"
    Then the exit code should be 0
    And the output should contain "5 numbers"

  Scenario: Generate password with custom symbol count
    When I run meowpass with "--symbols 4"
    Then the exit code should be 0
    And the output should contain "4 symbols"

  Scenario: Generate password with custom max length
    When I run meowpass with "--max-length 40"
    Then the exit code should be 0
    And the output should contain "max meow length 40"

  Scenario: Generate password with all custom options
    When I run meowpass with "--numbers 5 --symbols 3 --max-length 35"
    Then the exit code should be 0
    And the output should contain "5 numbers"
    And the output should contain "3 symbols"
    And the output should contain "max meow length 35"
