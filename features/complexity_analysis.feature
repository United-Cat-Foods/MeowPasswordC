Feature: Complexity Analysis
  As a user of MeowPassword
  I want passwords to be analyzed for complexity
  So that I know how secure my generated password is

  Scenario: Display complexity analysis for selected password
    When I run meowpass without arguments
    Then the exit code should be 0
    And the output should contain "Meow Complexity Analysis"
    And the output should contain "Tail Size:"
    And the output should contain "Ball of Yarn Entropy:"
    And the output should contain "Mashing Resistance:"
    And the output should contain "Shiny Foil Ball Uniqueness:"
    And the output should contain "Percent of Organic NonGMO Catnip:"
    And the output should contain "Overall Relavency:"

  Scenario: Each candidate has a complexity score
    When I run meowpass without arguments
    Then the exit code should be 0
    And each candidate should have a "Meow Score" line
