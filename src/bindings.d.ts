/**
 * Extend the global Window interface with custom bindings
 *
 * This provides TypeScript with the necessary type information to allow
 * the use of custom bindings in the global Window object.
 */

declare global {
  interface Window {
    count(direction: number): Promise<string>
    greet(name: string): Promise<string>
  }
}

// This export is here to ensure this file is treated as a module and not a script
export {}
