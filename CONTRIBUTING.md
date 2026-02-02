# YimMenu Contribution Guide

Thank you for considering contributing to YimMenuV2! This guide will help you get started.

## Important Rules

**PRs containing AI-generated code will NOT BE ACCEPTED!**

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/YimmenuEnhanced.git`
3. Create a new branch: `git checkout -b feature/your-feature-name`
4. Make your changes following the guidelines below
5. Test your changes thoroughly
6. Commit your changes with clear, descriptive commit messages
7. Push to your fork and submit a pull request

## Project Structure

- `core/` : Essential general features for the base
- `game/` : Game specific implemented things
  - `backend/` : Game state management and core game functionality
  - `commands/` : Command implementations
  - `features/` : Game features organized by category
  - `frontend/` : UI components
  - `hooks/` : Game hooks for intercepting functionality
  - `pointers/` : Game memory pointers

## Coding Standards

### Compiler

- **Use Clang instead of MSVC** and fix all compiler warnings
- Enable maximum warning levels during development
- Treat warnings as errors when possible

### Code Style

- Follow the `.clang-format` configuration provided in the repository
- Use meaningful variable and function names
- Keep functions focused and concise
- Add comments only when necessary to explain complex logic

### Modern C++ Practices

- Use C++23 features where appropriate
- Prefer `std::string_view` for immutable string parameters
- Use `std::to_array` instead of automatic deduction for constexpr arrays to prevent Clang compilation issues
- Use `static_cast` and `reinterpret_cast` instead of C-style casts
- Prefer smart pointers (`std::unique_ptr`, `std::shared_ptr`) over raw pointers when appropriate
- Use `auto` for complex types, but be explicit for clarity when needed
- Utilize range-based for loops where applicable

### Memory Management

- Avoid manual `new`/`delete` - use RAII and smart pointers
- Be cautious with game memory access - always validate pointers
- Use proper synchronization for multi-threaded code

## Implementing New Features

### Commands

All new features should be implemented as `Command` objects:

1. **Normal Command** (one-time execution):
   ```cpp
   class MyFeature : public Command
   {
       using Command::Command;
       virtual void OnCall() override
       {
           // Your feature implementation
       }
   };
   ```

2. **Looped Command** (executes every frame):
   ```cpp
   class MyLoopedFeature : public LoopedCommand
   {
       using LoopedCommand::LoopedCommand;
       virtual void OnTick() override
       {
           // Code that runs every frame when enabled
       }
   };
   ```

### File Organization

- Place your feature in the appropriate directory under `src/game/features/`
- Follow the existing organizational patterns (e.g., `self/`, `vehicle/`, `weapon/`)
- Create both `.hpp` and `.cpp` files for your feature

### Hooks

- Document what the hook does and why it's necessary
- Minimize hook overhead - only hook what's necessary
- Clean up hooks properly on shutdown

## Testing

- Test your changes in-game thoroughly
- Verify that existing features still work correctly
- Test edge cases and error conditions
- Ensure no crashes or memory leaks

## Pull Request Guidelines

### Before Submitting

- [ ] Code compiles without errors or warnings
- [ ] All changes have been tested in-game
- [ ] Code follows the project's style guidelines
- [ ] Commit messages are clear and descriptive
- [ ] No AI-generated code is included

### PR Description

Include in your pull request description:
- What does this PR do?
- Why is this change needed?
- How was it tested?
- Any known limitations or issues?
- Screenshots/videos if applicable (especially for UI changes)

### Review Process

- Maintainers will review your PR and may request changes
- Address review feedback promptly
- Be patient - reviews may take time
- Be open to suggestions and improvements

## Code of Conduct

Please note that this project has a [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you agree to abide by its terms.

## Questions?

If you have questions about contributing, feel free to:
- Open an issue for discussion
- Check existing issues and pull requests for similar topics
- Review the codebase for examples

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.