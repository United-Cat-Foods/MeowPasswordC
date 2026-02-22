Feature: Input Validation
  As a user of MeowPassword
  I want invalid inputs to be handled gracefully
  So that the tool always produces a usable password

  Scenario: Numbers option is clamped to valid range
    When I run meowpass with "--numbers 100"
    Then the exit code should be 0
    And the output should contain "10 numbers"

  Scenario: Max length is clamped to minimum
    When I run meowpass with "--max-length 5"
    Then the exit code should be 0
    And the output should contain "max meow length 15"

  Scenario: Max length is clamped to maximum
    When I run meowpass with "--max-length 999"
    Then the exit code should be 0
    And the output should contain "max meow length 50"
